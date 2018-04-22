#ifndef POINT_H
#define POINT_H

#include <QGraphicsScene>

class Point
{
public:
    double x;
    double y;

public:
    QGraphicsEllipseItem *ellipse;

public:
    Point();
    Point(double x, double y);
    void coord();
    void draw(QGraphicsScene *scene);
};

#endif // POINT_H
