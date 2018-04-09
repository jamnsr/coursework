/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape
{
  private:
    double cord1x;
    double cord2x;
    double cord3x;
    double cord1y;
    double cord2y;
    double cord3y;

  public:
    Triangle(double, double, double, double, double, double);
    bool checkPoint(double, double);

};

#endif
