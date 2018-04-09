/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#include "Image.h"

void Header::setMaxV(int v){
  maxV = v;
}

void Header::setImW(int w){
  imW = w;
}

void Header::setImH(int h){
  imH = h;
}

void Header::setMagic(string s){
  magic = s;
}

void Header::printHeader(ofstream& outF){
  outF << magic << endl;
  outF << imW << endl;
  outF << imH << endl;
  outF << maxV << endl;
}
