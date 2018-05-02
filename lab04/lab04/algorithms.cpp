#include "algorithms.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "drawer.h"

using namespace std;

#define PI 3.1415926535

void drawPoint(QGraphicsScene *scene, double x, double y, QPen pen) {
    Drawer *drawer = new Drawer();

    drawer->x = x;
    drawer->y = y;
    drawer->color = pen;

    scene->addItem(drawer);
}

int sign(double x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}

void circleCanon(QGraphicsScene *scene, int radius, QPen pen) {
    for (int x = 0; x < radius + 1; x++) {
        double y = round(sqrt(pow(radius, 2) - pow(x, 2)));

        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);
    }

    for (int y = 0; y < radius + 1; y++) {
        double x = round(sqrt(pow(radius, 2) - pow(y, 2)));

        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);
    }

    scene->update();
}

void circleParam(QGraphicsScene *scene, double radius, QPen pen) {
    int length = round(PI * radius / 2);

    for (int i = 0; i < length + 1; i++) {
        double x = round(radius * cos(i / radius));
        double y = round(radius * sin(i / radius));

        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);
    }

    scene->update();
}

void circleBrez(QGraphicsScene *scene, double radius, QPen pen) {
    // начальные значения
    double x = 0;
    double y = radius;

    double d = 2 - 2 * radius; // значение D(x,y)  при (0,R)
    double buf;

    while (y >= 0) {
        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);

        if (d < 0) { // пиксель лежит внутри окружности
            buf = 2 * d + 2 * y - 1;
            x++;

            if (buf <= 0) { // горизонтальный шаг
                d = d + 2 * x + 1;
            } else { // диагональный шаг
                y--;
                d = d + 2 * x - 2 * y + 2;
            }

            continue;
        } else if (d > 0) { // пиксель лежит вне окружности
            buf = 2 * d - 2 * x - 1;
            y--;

            if (buf > 0) { // вертикальный шаг
                d = d - 2 * y + 1;
            } else { // диагональный шаг
                x++;
                d = d + 2 * x - 2 * y + 2;
            }

            continue;
        } else if (d == 0.0) { // пиксель лежит на окружности
            x++; // диагональный шаг
            y--;
            d = d + 2 * x - 2 * y + 2;
        }
    }

    scene->update();
}

void circleMiddle(QGraphicsScene *scene, double radius, QPen pen) {
    // начальные значения
    double x = 0;
    double y = radius;

    double p = 5 / 4 - radius; // (x + 1)^2 + (y - 1/2)^2 - r^2

    while (true) {
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, -y, pen);
        drawPoint(scene, x, y, pen);

        drawPoint(scene, -y, x, pen);
        drawPoint(scene, y, -x, pen);
        drawPoint(scene, -y, -x, pen);
        drawPoint(scene, y, x, pen);

        x++;

        if (p < 0) { // средняя точка внутри окружности, ближе верхний пиксел, горизонтальный шаг
            p += 2 * x + 1;
        } else { // средняя точка вне окружности, ближе диагональный пиксел, диагональный шаг
            p += 2 * x - 2 * y + 5;
            y--;
        }

        if (x > y) break;
    }

    scene->update();
}

void ellipseCanon(QGraphicsScene *scene, double a, double b, QPen pen) {
    for (int x = 0; x < a + 1; x++) {
        double y = round(b * sqrt(1.0 - pow(x, 2) / a / a));

        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);
    }

    for (int y = 0; y < b + 1; y++) {
        double x = round(a * sqrt(1.0 - pow(y, 2) / b / b));

        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);
    }

    scene->update();
}

void ellipseParam(QGraphicsScene *scene, double a, double b, QPen pen) {
    double m = max(a, b);
    double length = round(PI * m / 2);

    for (int i = 0; i < length + 1; i++) {
        double x = round(a * cos(i / m));
        double y = round(b * sin(i / m));

        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);
    }

    scene->update();
}

void ellipseBrez(QGraphicsScene *scene, double a, double b, QPen pen) {
    // начальные значения
    double x = 0;
    double y = b;
    a = pow(a, 2);
    double d = round(b * b / 2 - a * b * 2 + a /2);
    b = pow(b, 2);

    double buf;

    while (y >= 0) {
        drawPoint(scene, x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, -x, -y, pen);

        if (d < 0) { // пиксель лежит внутри окружности
            buf = 2 * d + 2 * a * y - a;
            x++;

            if (buf <= 0) { // горизонтальный шаг
                d = d + 2 * b * x + b;
            } else { // диагональный шаг
                y--;
                d = d + 2 * b * x - 2 * a * y + a + b;
            }

            continue;
        } else if (d > 0) { // пиксель лежит вне окружности
            buf = 2 * d - 2 * b * x - b;
            y--;

            if (buf > 0) { // вертикальный шаг
                d = d - 2 * y * a + a;
            } else { // диагональный шаг
                x++;
                d = d + 2 * x * b - 2 * y * a + a + b;
            }

            continue;
        } else if (d == 0.0) { // пиксель лежит на окружности
            x++; // диагональный шаг
            y--;
            d = d + 2 * x * b - 2 * y * a + a + b;
        }
    }

    scene->update();
}

void ellipseMiddle(QGraphicsScene *scene, double a, double b, QPen pen) {
    // начальные значения
    double x = 0;
    double y = b;

    double p = b * b - a * a * b + 0.25 * a * a; // начальное значение параметра принятия решения в области tg<1

    while (2 * pow(b, 2) * x < 2 * a * a * y) { // пока тангенс угла наклона меньше 1
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, -y, pen);
        drawPoint(scene, x, y, pen);

        x++;

        if (p < 0) { // средняя точка внутри окружности, ближе верхний пиксел, горизонтальный шаг
            p += 2 * b * b * x + b * b;
        } else { // средняя точка вне окружности, ближе диагональный пиксел, диагональный шаг
            y--;
            p += 2 * b * b * x - 2 * a * a * y + b * b;
        }
    }

    p += 3/4 * (a * a + b * b) - b * b * x - a * a * y;

    while (y >= 0) {
        drawPoint(scene, -x, y, pen);
        drawPoint(scene, x, -y, pen);
        drawPoint(scene, -x, -y, pen);
        drawPoint(scene, x, y, pen);

        y--;

        if (p > 0) {
            p -= 2 * a * a * y - a * a;
        } else {
            x++;
            p += 2 * b * b * x - 2 * a * a * y + a * a;
        }
    }

    scene->update();
}
