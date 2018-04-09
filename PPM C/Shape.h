/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Shape
{
  private:
    unsigned char shapeR;
    unsigned char shapeG;
    unsigned char shapeB;

  public:
    void setColor(unsigned char, unsigned char, unsigned char);
    void printSC(ofstream&);

};

#endif
