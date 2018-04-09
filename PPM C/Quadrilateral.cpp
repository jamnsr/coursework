/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#include "Quadrilateral.h"

Quadrilateral::Quadrilateral(double c1x, double c1y, double c2x, double c2y,
                              double c3x, double c3y, double c4x, double c4y){
  this->cord1x = c1x;
  this->cord1y = c1y;
  this->cord2x = c2x;
  this->cord2y = c2y;
  this->cord3x = c3x;
  this->cord3y = c3y;
  this->cord4x = c4x;
  this->cord4y = c4y;

  setColor(240, 100, 3);
}

bool Quadrilateral::checkPoint(double testX, double testY){
  #define y1 cord1y
  #define y2 cord2y
  #define y3 cord3y
  #define y4 cord4y
  #define x1 cord1x
  #define x2 cord2x
  #define x3 cord3x
  #define x4 cord4x
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

  double d = 0;
  double e = 0;
  double f = 0;

  d = ((y4 - y3) * (x0 - x3) + (x3 - x4) * (y0 - y3)) / ((y4 - y3) * (x2 - x3) +
                                                        (x3 - x4) * (y2 - y3));
  e = ((y3 - y2) * (x0 - x3) + (x2 -x3) * (y0 - y3)) / ((y4 - y3) * (x2 - x3) +
                                                        (x3 - x4) * (y2 - y3));
  f = 1 - d - e;

  double g = 0;
  double h = 0;
  double i = 0;

  g = ((y4 - y3) * (x0 - x3) + (x3 - x4) * (y0 - y3)) / ((y4 - y3) * (x1 - x3) +
                                                        (x3 - x4) * (y1 - y3));
  h = ((y3 - y1) * (x0 - x3) + (x1 -x3) * (y0 - y3)) / ((y4 - y3) * (x1 - x3) +
                                                        (x3 - x4) * (y1 - y3));
  i = 1 - g - h;

  if((a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1) ||
     (d >= 0 && d <= 1 && e >= 0 && e <= 1 && f >= 0 && f <= 1) ||
     (g >= 0 && g <= 1 && h >= 0 && h <= 1 && i >= 0 && i <= 1)    ){
    return true;
  }
  else
    return false;
}
