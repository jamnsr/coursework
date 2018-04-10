/*************************
 *Jamal Nasser
 *Fall 2017
 *Basic implementation of Google's Pagerank Algorithm in C++
 *Takes in a formatted text document as input
 *************************/

#ifndef STRINGSET_H /* Prevent multiple inclusion... */
#define STRINGSET_H

#include <string>
using namespace std;

struct Node {
  string key;
  int index;
  Node *next;
  Node(string k, int i, Node *n) { key = k; index = i; next = n; }
  Node(string k, Node *n) { key = k; next = n; }
  Node() { key = ""; next = NULL; }
};

class Stringset {

 private:
  Node **table;  // array of pointers to linked lists
  int size;      // size of table, as currently allocated
  int num_elems; // number of elements stored in the table

 public:
  Stringset();
  ~Stringset();
  bool find(string key);
  int getIndex(string key);
  void insert(string key, int index);
  void remove(string key);
  void print(void);
};

#endif
