/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H
#include "Shape.h"

class Quadrilateral : public Shape
{
  private:
    double cord1x;
    double cord2x;
    double cord3x;
    double cord4x;
    double cord1y;
    double cord2y;
    double cord3y;
    double cord4y;

  public:
    Quadrilateral(double, double, double, double, double, double, double,
                                                                        double);
    bool checkPoint(double, double);

};

#endif
