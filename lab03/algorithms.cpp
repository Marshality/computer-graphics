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

void DDA_line(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
    double delta_x = abs(x1 - x2);
    double delta_y = abs(y1 - y2);

    double length = max(delta_x, delta_y);

    if (length == 0) {
        scene->addLine(x1, y1, x1, y1, pen);
        std::cout << "!" << std::endl;
        return;
    }

    double dx = (x2 - x1) / length;
    double dy = (y2 - y1) / length;

    double x = x1 + 0.5 * sign(dx);
    double y = y1 + 0.5 * sign(dy);

    while (length + 1 > 0) {
        scene->addLine(x, y, x, y, pen);
        x += dx;
        y += dy;
        length--;
    }
}

void BREZ_float(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
    if ((x1 == x2) && (y1 = y2)) {
        scene->addLine(x1, y1, x2, y2, pen);
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
        scene->addLine(x, y, x, y, pen);
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

void BREZ_int(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
    if ((x1 == x2) && (y1 = y2)) {
        scene->addLine(x1, y1, x2, y2, pen);
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
        scene->addLine(x, y, x, y, pen);
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

//void line_br_smooth(QGraphicsScene *scene, double x1, double y1, double x2, double y2, QPen pen) {
//    if ((x1 == x2) && (y1 = y2)) {
//        scene->addLine(x1, y1, x2, y2, pen);
//        return;
//    }

//    double dx = x2 - x1;
//    double dy = y2 - y1;

//    double sx = sign(dx);
//    double sy = sign(dy);
//    dx = abs(dx);
//    dy = abs(dy);

//    double x = x1;
//    double y = y1;

//  //    try:
//  //      h = dy / dx
//  //  except ZeroDivisionError:
//  //      h = 0
//  //double h = dy / dx;


//    bool isBlack = true;

//    if (pen == Qt::black) {
//        int i_max = 256;
//        isBlack = true;
//    }
//    else i_max = 100;

//    bool change = false;

//    if (dy > dx) {
//        dx = dy;
//        dy = dx;
//        change = true;
//        if (h) {
//            h = 1 / h;
//        }
//    }

//    h *= i_max;
//    double e = i_max/2;
//    double w = i_max - h;
//    int i = 1;
//    while (i <= dx) {
//        if (isBlack == false) {
//            QPen new = pen;
//            new.lighter(100 + e) // ???
//            win.pen.setColor(new)
//            win.image.setPixel(x, y, win.pen.color().rgba())
//        }
//        else:
//            new = QColor()
//            new.setRgb(0, 0, 0, alpha=255 - e)
//            win.pen.setColor(new)
//            win.image.setPixel(x, y, win.pen.color().rgba())
//        if e <= w:
//            if change:
//                y += sy
//            else:
//                x += sx
//            e += h
//        else:
//            x += sx
//            y += sy
//            e -= w
//        i += 1
//    }
//}
