#include <math.h>
#include "settings.h"
#include "functions.h"
#include <iostream>

#define PI    3.14159265
#define SCALE 10
#define PART  90

double convert(double y) {
    return 551 - y;
}

struct Point astroidFunction(int R, int t) {
    struct Point point;

    point.x = R * pow(cos(t * PI / 180), 3);
    point.y = R * pow(sin(t * PI / 180), 3);

    return point;
}

void createAstroid() {
    astroid.clear();

    for (int i = 0; i < PART * 4; i += 10) {
        struct Point point = astroidFunction(5, i);
        astroid.push_back(point);
    }
}

void createCube() {
    cube.clear();

    for (int i = 0; i < PART * 4; i += 90) {
        struct Point point = astroidFunction(5, i);
        cube.push_back(point);
    }
}

void draw(QGraphicsScene *scene) {
    QPolygon polygon;

    int size = astroid.size();

    for (int i = 0; i < size; i++) {
        polygon << QPoint(astroid[i].x * SCALE, convert(astroid[i].y) * SCALE);
    }

    scene->addPolygon(polygon);

    polygon.clear();
    size = cube.size();

    for (int i = 0; i < size; i++) {
        polygon << QPoint(cube[i].x * SCALE, convert(cube[i].y) * SCALE);
    }

    scene->addPolygon(polygon);
}

void moveFunction(double dx, double dy) {
    for (auto iterator = astroid.begin(); iterator < astroid.end(); iterator++) {
        iterator->x += dx;
        iterator->y += dy;
    }

    for (auto iterator = cube.begin(); iterator < cube.end(); iterator++) {
        iterator->x += dx;
        iterator->y += dy;
    }
}

void scaleFunction(double xm, double ym, double kx, double ky) {
    for (auto iterator = astroid.begin(); iterator < astroid.end(); iterator++) {
        iterator->x = iterator->x * kx + (1 - kx) * xm;
        iterator->y = iterator->y * ky + (1 - ky) * ym;
    }

    for (auto iterator = cube.begin(); iterator < cube.end(); iterator++) {
        iterator->x = iterator->x * kx + (1 - kx) * xm;
        iterator->y = iterator->y * ky + (1 - ky) * ym;
    }
}

void rotateFunction(double xc, double yc, double angle) {
    double temp_x, temp_y;

    double sint = sin(angle * PI / 180);
    double cost = cos(angle * PI / 180);

    for (auto iterator = astroid.begin(); iterator < astroid.end(); iterator++) {
        temp_x = xc + (iterator->x - xc) * cost + (iterator->y - yc) * sint;
        temp_y = yc + (iterator->y - yc) * cost - (iterator->x - xc) * sint;
        iterator->x = temp_x;
        iterator->y = temp_y;
    }

    for (auto iterator = cube.begin(); iterator < cube.end(); iterator++) {
        temp_x = xc + (iterator->x - xc) * cost + (iterator->y - yc) * sint;
        temp_y = yc + (iterator->y - yc) * cost - (iterator->x - xc) * sint;
        iterator->x = temp_x;
        iterator->y = temp_y;
    }
}

void copyVector(std::vector <struct Point> copy, std::vector <struct Point> original) {
    // copy
}
