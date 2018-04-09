/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#ifndef IMAGE_H
#define IMAGE_H
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "Header.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Quadrilateral.h"

using namespace std;

class Image
{
  private:
    Header head;
    unsigned char r;
    unsigned char g;
    unsigned char b;

  public:
    void setHead(int, int, int, string);
    void printHead(ofstream&);
    void setBG(unsigned char, unsigned char, unsigned char);
    void printBG(ofstream&);

};
#endif
