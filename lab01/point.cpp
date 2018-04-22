#include "point.h"
#include <iostream>
#include "lab01.h"
#include "functions.h"
#include <QPen>
#include <QBrush>

using namespace std;

Point::Point() {}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

void Point::coord() {
    cout << "\n" << this->x << " - " << this->y << endl;
}

void Point::draw(QGraphicsScene *scene) {
    QPen bluepen(Qt::darkGray);
    QBrush bluebrush(Qt::darkGray);
    this->ellipse = scene->addEllipse(this->x * 30 - 2.5, reverse_y(this->y) * 30 - 2.5, 5, 5, bluepen, bluebrush);
}
