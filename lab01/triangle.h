#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "line.h"
#include "height.h"

class Triangle
{
public:
    Point pa;
    Point pb;
    Point pc;

public:
    struct line lines[3];
    struct height heights[3];
    double maxHeight;
    int index;

public:
    QGraphicsLineItem *line;

public:
    Triangle(Point point_a, Point point_b, Point point_c);
    void coord();
    int findMaxHeight();
    void draw(QGraphicsScene *scene);
    void getLines();
    void getHeights();
    void getLinesCrossingPoint();
};

#endif // TRIANGLE_H
