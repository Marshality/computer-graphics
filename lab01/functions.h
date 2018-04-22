#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "point.h"
#include "triangle.h"

double getLength(Point first, Point second);
double allls(int a, int b);
double determinant(double a, double b, double c, double d);
int getTriangles();
bool validator(Point pa, Point pb, Point pc);
double reverse_y(double y);

#endif // FUNCTIONS_H
