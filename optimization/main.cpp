/*************************
 *Jamal Nasser
 *Fall 2017
 *Program demonstrating multiple optimization algorithms concerning
 *maximizing the amount of 'tastiness' in a 'candy bag'
 *Each line from input text describes a the 'weight' and 'taste' of a candy

 // Demonstrates: Greedy Heuristic, Iterative Refinement, Recursive search
 *************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>

using namespace std;

const int N = 16;

struct Bag {
  int weight, taste;
};

struct Candy {
  int weight, taste;
  double taste_density;
  int bagNum;
};

int bestTasteExhaustive;
Candy C[N];
Bag greedyBags[4];
Bag iterativeBags[4];


Candy bestIterativeC[N];
Bag bestIterativeB[4];

void moveCandyToBag(int candyNum, Bag b[], int numBagMoveTo){
  int currentBag = C[candyNum].bagNum;
  if(C[candyNum].bagNum != 0){
    b[currentBag].weight -= C[candyNum].weight;
    b[currentBag].taste -= C[candyNum].taste;
  }
  C[candyNum].bagNum = numBagMoveTo;
  b[numBagMoveTo].weight += C[candyNum].weight;
  b[numBagMoveTo].taste += C[candyNum].taste;
}
void emptyBags(Bag b[]){
  for(int i = 0; i < N; i++)
    C[i].bagNum = 0;
  for(int j = 1; j < 4; j++){
    b[j].weight = 0;
    b[j].taste = 0;
  }
}
void repairBags(Bag b[]){
  for(int i = 1; i < 4; i++){
    for(int j = 0; j < N; j++){
      if(b[i].weight + C[j].weight <= 2000 && C[j].bagNum == 0){
        b[i].weight += C[j].weight;
        b[i].taste += C[j].taste;
        C[j].bagNum = i;
      }
    }
  }
  for(int i = 1; i < 4; i++){
    for(int j = N - 1; j >= 0; j--){
      if(b[i].weight > 2000 && C[j].bagNum == i){
        b[i].weight -= C[j].weight;
        b[i].taste -= C[j].taste;
        C[j].bagNum = 0;
      }
    }
  }
}
int totalTaste(Bag b[]){
  int total = 0;
  for(int i = 1; i < 4; i++)
    total += b[i].taste;

  return total;
}
void copyBest(Bag b[]){
  for(int i = 1; i < 4; i++)
    bestIterativeB[i] = b[i];
}


void pExhaust(int index, int bag1W, int bag2W, int bag3W, int bag1T, int bag2T, int bag3T)
{
  // Prune the search
  if (bag1W > 2000 || bag2W > 2000 || bag3W > 2000)
    return;

  if (index == N-1) {
    int totalTaste = bag1T + bag2T + bag3T;
    if (totalTaste > bestTasteExhaustive)
      bestTasteExhaustive = totalTaste;
    return;
  }
  for (int j=0; j<4; j++){
    int _bag1W = j == 1 ? bag1W + C[index].weight : bag1W;
    int _bag2W = j == 2 ? bag2W + C[index].weight : bag2W;
    int _bag3W = j == 3 ? bag3W + C[index].weight : bag3W;
    int _bag1T = j == 1 ? bag1T + C[index].taste : bag1T;
    int _bag2T = j == 2 ? bag2T + C[index].taste : bag2T;
    int _bag3T = j == 3 ? bag3T + C[index].taste : bag3T;
    pExhaust(index+1, _bag1W, _bag2W, _bag3W, _bag1T, _bag2T, _bag3T);
  }
}

int main(void)
{
  //Read in candy to memory
  ifstream fin;
  int read_weight, read_taste;
  bool spaceExists;

  fin.open ("candy.txt");
  int count = 0;
  while (fin >> read_weight >> read_taste) {
    C[count].weight = read_weight;
    C[count].taste = read_taste;
    C[count].taste_density = (double)read_taste / read_weight;
    count++;
  }
  fin.close();

  /* PART 1 : GREEDY HEURISTIC*/
  emptyBags(greedyBags);

  //Sort based on taste_density
  for (int i = 0; i < N-1; i++)
    for (int j = 0; j < N-i-1; j++)
      if (C[j].taste_density < C[j+1].taste_density)
        swap(C[j], C[j+1]);

  //Greedy
  for(int i = 1; i < 4; i++){
    for(int j = 0; j < N; j++){
      if(greedyBags[i].weight + C[j].weight <= 2000 && C[j].bagNum == 0)
        moveCandyToBag(j, greedyBags, i);
    }
  }

  cout << "Greedy: " << totalTaste(greedyBags) << endl;


  /* PART 2 : ITERATIVE REFINEMENT*/
  int best = 0;
  Candy tempBestC[N];
  Bag tempBestB[4];
  for(int i = 0; i < 1000; i++){
    emptyBags(iterativeBags);
    //Random Assignment
    for(int j = 1; j < 4; j++){
      spaceExists = true;
      while(spaceExists){
        int randNum = rand() % 16;
        if(iterativeBags[j].weight + C[randNum].weight <= 2000 && C[randNum].bagNum == 0)
          moveCandyToBag(randNum, iterativeBags, j);
        else if(C[randNum].bagNum == 0)
          spaceExists = false;

      }
    }
    //Iterative Refinement
    for(int i = 0; i < N; i++){
      for(int j = 1; j < 4; j++){
        if(C[i].bagNum == j){
          //Refine
          int tasteBeforeRefine = totalTaste(iterativeBags);
          int nextBag = (j+1 == 4 ? 1 : j+1);
          moveCandyToBag(i, iterativeBags, nextBag);

          //Repair
          repairBags(iterativeBags);

          //Check if better
          if(tasteBeforeRefine > totalTaste(iterativeBags)){
            moveCandyToBag(i, iterativeBags, j);
            repairBags(iterativeBags);
          }
          else if(best < totalTaste(iterativeBags)){
            best = totalTaste(iterativeBags);
            copyBest(iterativeBags);
          }

        }
      }
    }
  }

  cout << "Refinement: " << totalTaste(bestIterativeB) << endl;


  /* PART 3 : RECURSIVE EXHAUSTIVE SEARCH */
  pExhaust(0, 0, 0, 0, 0, 0, 0);
  cout << "Exhaustive: " << bestTasteExhaustive << endl;

  return 0;
}
