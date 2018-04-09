/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#include "Image.h"

void Image::setHead(int w, int h, int maxV, string s){
  head.setImW(w);
  head.setImH(h);
  head.setMaxV(maxV);
  head.setMagic(s);
}

void Image::printHead(ofstream& outF){
  head.printHeader(outF);
}

void Image::setBG(unsigned char r, unsigned char g, unsigned char b){
  this->r = r;
  this->g = g;
  this->b = b;
}

void Image::printBG(ofstream& outF){
  outF << this->r << this->g << this->b;  
}
