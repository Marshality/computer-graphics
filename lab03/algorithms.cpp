#include "algorithms.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "drawer.h"

using namespace std;

void drawPoint(QGraphicsScene *scene, double x, double y, QPen pen) {
    Drawer *drawer = new Drawer();

    drawer->x = x;
    drawer->y = y;
    drawer->color = pen;

    scene->addItem(drawer);
}

double sign(double x) {
    if (x == 0)
        return 0;
  return x / abs(x);
}

void DDA_line(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
    if (x1 == x2 && y1 == y2) {
        drawPoint(scene, x1, y1, pen);
        return;
    }

    double x = x1, y = y1;

    double delta_x = int(x2 - x1);
    double delta_y = int(y2 - y1);

    int length;
    if (abs(delta_x) > abs(delta_y)) {
        length = int(abs(delta_x));
    } else {
        length = int(abs(delta_y));
    }

    double dx = delta_x / length;
    double dy = delta_y / length;

    while (length + 1 > 0) {
        drawPoint(scene, round(x), round(y), pen);
        x += dx;
        y += dy;
        length--;
    }

    scene->update();
}

void BREZ_float(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
    if ((x1 == x2) && (y1 = y2)) {
        drawPoint(scene, x1, y1, pen);
        return;
    }

    double dx = int(x2 - x1);
    double dy = int(y2 - y1);

    double sx = sign(dx);
    double sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    double x = x1;
    double y = y1;

    bool change = false;

    if (dy > dx) {
        double temp = dx;
        dx = dy;
        dy = temp;

        change = true;
    }

    double tg = abs(dy / dx);
    double error = tg - 0.5;

    int iterator = 1;
    while (iterator <= dx) {
        drawPoint(scene, x, y, pen);

        if (error >= 0) {
            if (change == false) y += sy;
            else x += sx;
            error--;
        }

        if (error < 0) {
            if (change == false) x += sx;
            else y += sy;
            error += tg;
        }

        iterator++;
    }

    scene->update();
}

void BREZ_int(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
    if ((x1 == x2) && (y1 = y2)) {
        drawPoint(scene, x1, y1, pen);
        return;
    }

    double dx = int(x2 - x1);
    double dy = int(y2 - y1);

    double sx = sign(dx);
    double sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    double x = x1;
    double y = y1;

    bool change = false;

    if (dy > dx) {
        double temp = dx;
        dx = dy;
        dy = temp;

        change = true;
    }

    double error = 2 * dy - dx;

    int iterator = 1;
    while (iterator <= dx) {
        drawPoint(scene, x, y, pen);

        if (error >= 0) {
            if (change == false) y += sy;
            else x += sx;
            error -= 2 * dx;
        }

        if (error < 0) {
            if (change == false) x += sx;
            else y += sy;
            error += 2 * dy;
        }

        iterator++;
    }

    scene->update();
}

void BREZ_smooth(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
    if (x1 == x2 && y1 == y2) {
        drawPoint(scene, x1, y1, pen);
        return;
    }

    double x = x1;
    double y = y1;

    double dx = int(x2 - x1);
    double dy = int(y2 - y1);

    double sx = sign(dx);
    double sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool change = false;

    double tg;
    if (dx == 0) tg = 1;
    else tg = dy / dx;

    double saturation = 100;

    if (dy > dx) {
        dx = dy;
        tg = 1 / tg;
        change = true;
    }

    tg *= saturation;
    double error = 0.5;
    double w = saturation - tg;

    //LIGHTER
    QColor new_pen = pen.color();
    new_pen.setAlpha(100 + error);
    pen.setColor(new_pen);
    drawPoint(scene, x, y, pen);

    while (dx + 1 > 0) {
        if (error <= w) {
            if (change == true) y += sy;
            else x += sx;
            error += tg;
        } else {
            x += sx;
            y += sy;
            error -= w;
        }

        //LIGHTER
        new_pen = pen.color();
        new_pen.setAlpha(40 + error);
        pen.setColor(new_pen);
        drawPoint(scene, x, y, pen);
        dx--;
    }

    scene->update();
}

