#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QGraphicsScene>

void drawPoint(QGraphicsScene *scene, double x, double y, QPen pen);
double sign(double x);
void DDA_line(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen);
void BREZ_float(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen);
void BREZ_int(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen);
void BREZ_smooth(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen);

#endif // ALGORITHMS_H
