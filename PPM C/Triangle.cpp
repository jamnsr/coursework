/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#include "Triangle.h"

Triangle::Triangle(double c1x, double c1y, double c2x, double c2y,
                                                        double c3x, double c3y){
  this->cord1x = c1x;
  this->cord1y = c1y;
  this->cord2x = c2x;
  this->cord2y = c2y;
  this->cord3x = c3x;
  this->cord3y = c3y;

  setColor(100,50,40);

}
bool Triangle::checkPoint(double testX, double testY){
  #define y1 cord1y
  #define y2 cord2y
  #define y3 cord3y
  #define x1 cord1x
  #define x2 cord2x
  #define x3 cord3x
  #define x0 testX
  #define y0 testY

  double a = 0;
  double b = 0;
  double c = 0;

  a = ((y2 - y3) * (x0 - x3) + (x3 - x2) * (y0 - y3)) / ((y2 - y3) * (x1 - x3) +
                                                        (x3 - x2) * (y1 - y3));
  b = ((y3 - y1) * (x0 - x3) + (x1 -x3) * (y0 - y3)) / ((y2 - y3) * (x1 - x3) +
                                                        (x3 - x2) * (y1 - y3));
  c = 1 - a - b;


  if(a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1){
    return true;
  }
  else
    return false;
}
