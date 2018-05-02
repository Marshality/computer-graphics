#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QGraphicsScene>

void drawPoint(QGraphicsScene *scene, double x, double y, QPen pen);
int sign(double x);
void circleCanon(QGraphicsScene *scene, int radius, QPen pen);
void circleParam(QGraphicsScene *scene, double radius, QPen pen);
void circleBrez(QGraphicsScene *scene, double radius, QPen pen);
void circleMiddle(QGraphicsScene *scene, double radius, QPen pen);

#endif // ALGORITHMS_H
