#include "algorithms.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;



double sign(double x) {
    if (x == 0)
        return 0;
  return x / abs(x);
}

void DDA_line(QImage &image, double x1, double y1, double x2, double y2, QPen pen) {
    if (x1 == x2 && y1 == y2) {
        image.setPixel(x1, y1, pen.color().rgb());
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
        image.setPixel(round(x), round(y), pen.color().rgb());
        x += dx;
        y += dy;
        length--;
    }
}

void BREZ_float(QImage &image, double x1, double y1, double x2, double y2, QPen pen) {
    if ((x1 == x2) && (y1 = y2)) {
        image.setPixel(x1, y1, pen.color().rgb());
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

    double tg = dy / dx;
    double error = tg - 0.5;

    int iterator = 1;
    while (iterator <= dx) {
        image.setPixel(x, y, pen.color().rgb());

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
}

void BREZ_int(QImage &image, double x1, double y1, double x2, double y2, QPen pen) {
    if ((x1 == x2) && (y1 = y2)) {
        image.setPixel(x1, y1, pen.color().rgb());
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
        image.setPixel(x, y, pen.color().rgb());

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
}

void BREZ_smooth(QImage &image, double x1, double y1, double x2, double y2, QPen pen) {
    if (x1 == x2 && y1 == y2) {
        image.setPixel(x1, y1, pen.color().rgb());
        return;
    }

    double x = x1;
    double y = y1;

    double dx = int(x2 - x1);
    double dy = int(y2 - y1);

    double sx = sign(dx);
    double sy = sign(dy);

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

    pen.color() = pen.color().lighter(round(saturation / 2));
    image.setPixel(x, y, pen.color().rgb());

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

        pen.color() = pen.color().lighter(round(error));
        image.setPixel(x, y, pen.color().rgb());
        dx--;
    }
}

