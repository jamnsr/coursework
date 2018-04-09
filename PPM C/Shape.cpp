/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#include "Shape.h"

void Shape::setColor(unsigned char r, unsigned char g, unsigned char b){
  this->shapeR = r;
  this->shapeG = g;
  this->shapeB = b;
}

void Shape::printSC(ofstream& outF){
  outF << shapeR << shapeG << shapeB;
}
