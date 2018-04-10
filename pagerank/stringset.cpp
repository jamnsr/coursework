/*************************
 *Jamal Nasser
 *Fall 2017
 *Basic implementation of Google's Pagerank Algorithm in C++
 *Takes in a formatted text document as input
 *************************/


#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int hash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

/* Allocate a table of pointers to nodes, all initialized to NULL */
Node **allocate_table(int size)
{
  Node **table = new Node *[size];
  for (int i=0; i<size; i++)
    table[i] = NULL;
  return table;
}

Stringset::Stringset()
{
  size = 4; // initial size of table
  table = allocate_table(size);
  num_elems = 0;
}

Stringset::~Stringset()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}

/* Return true if key is in the set */
bool Stringset::find(string key)
{
  int h = hash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}

/* Return index if key is in the set */
int Stringset::getIndex(string key)
{
  assert (find(key));
  int h = hash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return n->index;
    n = n->next;
  }
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key, int index)
{
  assert (!find(key));
  num_elems++;

  // Allocate new table of twice the size,
  // re-insert all keys into new table, and de-allocate old table.
  if (num_elems == size) {
    size *= 2;
    Node **oldTable = table;
    table = allocate_table(size);

    for(int i = 0; i<(size/2); i++){
      Node* oldNode = oldTable[i];
      while(oldNode != NULL){
        int h = hash(oldNode->key, size);
        Node *n = table[h];
        table[h] = new Node(oldNode->key, oldNode->index, n);

        oldNode = oldNode->next;
      }
    }
    delete [] oldTable;
  }

  // Insert new element
  // use hash function to convert string to number
  int h = hash(key, size);
  // access the hash value in table[?] & insert it after head
  Node *n = table[h];
  table[h] = new Node(key, index, n);

}

/* Removes a key.  It is an error if key isn't in the set */
void Stringset::remove(string key)
{
  assert (find(key));
  num_elems--;

  //hash to get to location
  int h = hash(key, size);
  Node *n = table[h]->next;
  Node *current = table[h];

  //Remove from beginning
  if(current->key == key){
    table[h] = table[h] -> next;
  }
  //Remove from middle or end
  else{
    while (n->key != key) {
      n = n->next;
      current = current->next;
    }
    current->next = n->next;
  }
}

void Stringset::print(void)
{
  for(int i = 0; i<size; i++){
    Node *n = table[i];
    while(n != NULL){
      cout << n->key << endl;
      n = n->next;
    }
  }
}
