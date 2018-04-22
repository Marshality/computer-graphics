#include "triangle.h"
#include "functions.h"
#include <iostream>
#include <QPen>

Triangle::Triangle(Point point_a, Point point_b, Point point_c) {
    this->pa = point_a;
    this->pb = point_b;
    this->pc = point_c;

    this->getLines();
    this->getHeights();
    this->getLinesCrossingPoint();
    this->index = this->findMaxHeight();
}

void Triangle::coord() {
    this->pa.coord();
    this->pb.coord();
    this->pc.coord();
}

void Triangle::getLines() {
    this->lines[0].pa = this->pa;
    this->lines[0].pb = this->pb;

    this->lines[1].pa = this->pb;
    this->lines[1].pb = this->pc;

    this->lines[2].pa = this->pc;
    this->lines[2].pb = this->pa;

    for (int i = 0; i < 3; i++) {
        this->lines[i].a = this->lines[i].pa.y - this->lines[i].pb.y;
        this->lines[i].b = this->lines[i].pb.x - this->lines[i].pa.x;
        this->lines[i].c = (this->lines[i].pa.x * this->lines[i].pb.y) - \
                                (this->lines[i].pb.x * this->lines[i].pa.y);
    }
}

void Triangle::getHeights() {
    this->heights[0].vertice = this->pc;
    this->heights[0].other1 = this->pa;
    this->heights[0].other2 = this->pb;

    this->heights[1].vertice = this->pa;
    this->heights[1].other1 = this->pb;
    this->heights[1].other2 = this->pc;

    this->heights[2].vertice = this->pb;
    this->heights[2].other1 = this->pa;
    this->heights[2].other2 = this->pc;

    for (int i = 0; i < 3; i++) {
        this->heights[i].a = this->lines[i].b;
        this->heights[i].b = -(this->lines[i].a);
        this->heights[i].c = (this->lines[i].a * this->heights[i].vertice.y) - \
                                  (this->lines[i].b * this->heights[i].vertice.x);
    }
}

void Triangle::getLinesCrossingPoint() {
    for (int i = 0; i < 3; i++) {
        double d  = determinant(this->lines[i].a , this->lines[i].b, this->heights[i].a, this->heights[i].b);
        double dx = determinant(-this->lines[i].c, this->lines[i].b, -this->heights[i].c, this->heights[i].b);
        double dy = determinant(this->lines[i].a, -this->lines[i].c, this->heights[i].a, -this->heights[i].c);

        this->heights[i].crossing.x = dx / d;
        this->heights[i].crossing.y = dy / d;
    }
}

int Triangle::findMaxHeight() {
    double height1 = getLength(this->heights[0].vertice, this->heights[0].crossing);
    double height2 = getLength(this->heights[1].vertice, this->heights[1].crossing);
    double height3 = getLength(this->heights[2].vertice, this->heights[2].crossing);
    int indicator;

    if (height1 > height2 && height1 > height3) {
        this->maxHeight = height1;
        indicator = 0;
    } else if (height2 > height3) {
        this->maxHeight = height2;
        indicator = 1;
    } else {
        this->maxHeight = height3;
        indicator = 2;
    }

    return indicator;
}

void Triangle::draw(QGraphicsScene *scene) {
    scene->addLine(this->lines[0].pa.x * 30, reverse_y(this->lines[0].pa.y) * 30, this->lines[0].pb.x * 30, reverse_y(this->lines[0].pb.y) * 30);
    scene->addLine(this->lines[1].pa.x * 30, reverse_y(this->lines[1].pa.y) * 30, this->lines[1].pb.x * 30, reverse_y(this->lines[1].pb.y) * 30);
    scene->addLine(this->lines[2].pa.x * 30, reverse_y(this->lines[2].pa.y) * 30, this->lines[2].pb.x * 30, reverse_y(this->lines[2].pb.y) * 30);

    QPen red(Qt::red);
    QPen green(Qt::green);

    scene->addLine(this->heights[this->index].vertice.x * 30, reverse_y(this->heights[this->index].vertice.y) * 30, \
                   this->heights[this->index].crossing.x * 30, reverse_y(this->heights[this->index].crossing.y) * 30, red);
    if (getLength(this->heights[this->index].other1, this->heights[this->index].crossing) < \
            getLength(this->heights[this->index].other2, this->heights[this->index].crossing)) {
        scene->addLine(this->heights[this->index].other1.x * 30, reverse_y(this->heights[this->index].other1.y) * 30, \
                       this->heights[this->index].crossing.x * 30, reverse_y(this->heights[this->index].crossing.y) * 30, green);
    } else {
        scene->addLine(this->heights[this->index].other2.x * 30, reverse_y(this->heights[this->index].other2.y) * 30, \
                       this->heights[this->index].crossing.x * 30, reverse_y(this->heights[this->index].crossing.y) * 30, green);
    }
}
