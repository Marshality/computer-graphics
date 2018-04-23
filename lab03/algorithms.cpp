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
    double delta_x = abs(x1 - x2);
    double delta_y = abs(y1 - y2);

    double length = max(delta_x, delta_y);

    if (length == 0) {
        image.setPixel(x1, y1, pen.color().rgb());
        return;
    }

    double dx = (x2 - x1) / length;
    double dy = (y2 - y1) / length;

    double x = x1 + 0.5 * sign(dx);
    double y = y1 + 0.5 * sign(dy);

    while (length + 1 > 0) {
        image.setPixel(x, y, pen.color().rgb());
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

    double dx = x2 - x1;
    double dy = y2 - y1;

    double sx = sign(dx);
    double sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    double x = x1;
    double y = y1;

    bool change = false;

    if (dy > dx) {
        dx = dy;
        dy = dx;

        change = true;
    }

    double h = dy / dx;

    double e = h - 0.5;

    int i = 1;
    while (i <= dx) {
        image.setPixel(x, y, pen.color().rgb());
        if (e >= 0) {
            if (change == false) y += sy;
            else x += sx;
            e--;
        }

        if (e < 0) {
            if (change == false) x += sx;
            else y += sy;
            e += h;
        }

        i++;
    }
}

void BREZ_int(QImage &image, double x1, double y1, double x2, double y2, QPen pen) {
    if ((x1 == x2) && (y1 = y2)) {
        image.setPixel(x1, y1, pen.color().rgb());
        return;
    }

    double dx = x2 - x1;
    double dy = y2 - y1;

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

    double e = 2 * dy - dx;

    int i = 1;
    while (i <= dx) {
        image.setPixel(x, y, pen.color().rgb());
        if (e >= 0) {
            if (change == true) y += sy;
            else x += sx;
            e -= 2 * dx;
        }

        if (e < 0) {
            if (change == true) x += sx;
            else y += sy;
            e += (2 * dy);
        }

        i++;
    }
}

void BREZ_smooth(QImage &image, double x1, double y1, double x2, double y2, QPen pen) { // huinya
    if ((x1 == x2) && (y1 = y2)) {
        image.setPixel(x1, y1, pen.color().rgb());
        return;
    }

    double dx = x2 - x1;
    double dy = y2 - y1;

    double sx = sign(dx);
    double sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);

    double x = x1;
    double y = y1;

  //    try:
  //      h = dy / dx
  //  except ZeroDivisionError:
  //      h = 0
  //double h = dy / dx;
    double h;

    if (dx != 0) {
        h = dy / dx;
    } else {
        h = 0;
    }

    bool isBlack = false;
    int i_max;
    if (pen.color() == Qt::black) {
        i_max = 256;
        isBlack = true;
    }
    else i_max = 100;

    bool change = false;

    if (dy > dx) {
        dx = dy;
        dy = dx;
        change = true;
        if (h) {
            h = 1 / h;
        }
    }

    h *= i_max;
    double e = i_max / 2;
    double w = i_max - h;
    int i = 1;
    QColor new_pen;
    while (i <= dx) {
        if (isBlack == false) {
            new_pen = pen.color();
            new_pen.lighter(100 + e); // ???
            pen.setColor(new_pen);
            image.setPixel(x, y, pen.color().rgb());
        } else {
            new_pen.setRgb(0, 0, 0, 255 - e);
            pen.setColor(new_pen);
            image.setPixel(x, y, pen.color().rgb());
        }
        if (e <= w) {
            if (change)
                y += sy;
            else
                x += sx;
            e += h;
        } else {
            x += sx;
            y += sy;
            e -= w;
        i += 1;
        }
    }
}
