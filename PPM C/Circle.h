/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape
{
  private:
    double cord1x;
    double cord1y;
    int rad;


  public:
    Circle(double, double, int);
    bool checkPoint(double, double);

};

#endif
