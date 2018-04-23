#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QGraphicsScene>

double sign(double x);
void DDA_line(QImage &image, double x1, double y1, double x2, double y2, QPen pen);
void BREZ_float(QImage &image, double x1, double y1, double x2, double y2, QPen pen);
void BREZ_int(QImage &image, double x1, double y1, double x2, double y2, QPen pen);
void BREZ_smooth(QImage &image, double x1, double y1, double x2, double y2, QPen pen);

#endif // ALGORITHMS_H
