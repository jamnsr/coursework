/*************************
 *Jamal Nasser
 *Fall 2017
 *Basic implementation of Google's Pagerank Algorithm in C++
 *Takes in a formatted text document as input
 *************************/

#include <iostream>
#include <string>
#include <fstream>
#include "stringset.h"
using namespace std;

struct Page {
  string URL;
  double weight;
  double new_weight;
  Node *wordsHead;
  Node *linksHead;
  int links;
  Page()
  {
    URL = "";
    weight = 0.0;
    new_weight = 0.0;
    wordsHead = NULL;
    linksHead = NULL;
    links = 0;
  }
};

struct Word {
  string word;
  Node *pagesHead;
  Word()
  {
    word = "";
    pagesHead = NULL;
  }
};

int main(void)
{
  Stringset S, W;
  int c, i, totalWords = 0;
  int count = 0;
  ifstream fin;
  string s;

  cout << "Loading please wait..." << endl;

  //Get # of pages that need to be stored, also hash all newpage URLs
  fin.open("webpages.txt");
  while (fin >> s) {
    if(s == "NEWPAGE"){
      fin >> s;
      S.insert(s, count);
      count++;
    }
  }
  fin.close();

  //Store pages in memory
  Page* p = new Page[count];
  fin.open("webpages.txt");
  fin >> s;
  for(int i = 0; i < count; i++){
    fin >> p[i].URL;
    fin >> s;
    while(s != "NEWPAGE"){
      //Add word
      if (s.substr(0, 7) != "http://")
      {
        Node *n = p[i].wordsHead;
        p[i].wordsHead = new Node(s, n);
        if(!W.find(s)){
          W.insert(s, totalWords);
          totalWords++;
        }
      }
      //Add link
      else if (s.substr(0, 7) == "http://")
      {
        //only add if valid link
        if(S.find(s)){
          Node *n = p[i].linksHead;
          p[i].linksHead = new Node(s, S.getIndex(s), n);
          p[i].links++;
        }
      }
      //Check if more reading is necessary
      if(fin.eof())
        break;
      else
        fin >> s;
    }
  }
  fin.close();

  //Pagerank Calculations
  for (c = 0; c < count; c++){
    p[i].weight = 1.0 / count;
  }
  for (c = 0; c < 50; c++){
    for (i = 0; i < count; i++){
      p[i].new_weight = 0.1 / count;
    }
    for (i = 0; i < count; i++){
      for (Node *n = p[i].linksHead; n != NULL; n=n->next){
        p[n->index].new_weight += 0.9 * p[i].weight / p[i].links;
      }
    }
    for (i = 0; i < count; i++){
      p[i].weight = p[i].new_weight;
    }
  }

  //Inverted Index
  Word *wordsArray = new Word[totalWords];
  for (i = 0; i < count; i++){
    for (Node *n = p[i].wordsHead; n != NULL; n=n->next){
      Node *temp = wordsArray[W.getIndex(n->key)].pagesHead;
      wordsArray[W.getIndex(n->key)].pagesHead = new Node(p[i].URL, temp);
    }
  }

  //User Search
  int scaleFactor = 100 * count;
  cout << "Enter a string to search for: " << endl;
  cin >> s;
  Node *n = wordsArray[W.getIndex(s)].pagesHead;
  for (n; n != NULL; n=n->next){
    cout << (int)(scaleFactor * p[(S.getIndex(n->key))].weight);
    cout << " " + n->key << endl;
  }

  //Free memory
  delete[] p;
  delete[] wordsArray;

  return 0;

}
