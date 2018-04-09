/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#ifndef HEADER_H
#define HEADER_H
#include <string>
using namespace std;

class Header
{
  private:
    string magic;
    int imW;
    int imH;
    int maxV;

  public:
    void setMaxV(int);
    void setImW(int);
    void setImH(int);
    void setMagic(string);
    void printHeader(ofstream&);


};

#endif
