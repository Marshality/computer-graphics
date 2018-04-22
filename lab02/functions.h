#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "point.h"
#include <QGraphicsScene>

double convert(double y);
struct Point astroidFunction(int R, int t);
void createAstroid();
void createCube();
void draw(QGraphicsScene *scene);
void moveFunction(double dx, double dy);
void scaleFunction(double xm, double ym, double kx, double ky);
void rotateFunction(double xc, double yc, double angle);

#endif // FUNCTIONS_H
