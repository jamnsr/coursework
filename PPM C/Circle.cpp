/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#include "Circle.h"
#include <cmath>

Circle::Circle(double c1x, double c1y, int radius){
  this->cord1x = c1x;
  this->cord1y = c1y;
  this->rad = radius;

  setColor(49,14,81);
}
bool Circle::checkPoint(double x, double y){
  double d;
  d = sqrt(pow((x - cord1x), 2) + pow((y - cord1y), 2));
  if(d <= rad){
    return true;
  }
  else{
    return false;
  }

}
