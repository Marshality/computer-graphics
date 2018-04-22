#include "functions.h"
#include <math.h>
#include <iostream>
#include "settings.h"
#include "lab01.h"

using namespace std;

double reverse_y(double y) {
    return 501 - y;
}

double getLength(Point first, Point second) {
    return sqrt(pow((second.x - first.x), 2) + pow((second.y - first.y), 2));
}

/*
 * Линейные коэффициенты для стороны:
 * pa; pb - точки;
 * a: (pa.y - pb.y);
 * b: (pb.x - pa.x);
 * c: (pa.x * pb.y - pb.x * pa.y);
 *
 * Коэффициенты высоты:
 * a: (b-стороны);
 * b: (-a-стороны);
 * c: (a-стороны * p.y - b-стороны * p.x)
 *
 * Точка пересечения:
 * func: [Получение детерминанта 3х3 матрицы];
 * func: [Точка пересечения] (метод Крамера);
 *
 * a b c
 * a b c
 *
 * 1: a b
 *    a b
 *
 * 2: -c b
 *    -c b
 *
 * 3: a -c
 *    a -c
 *
 * Точка:
 * x: 2 / 1;
 * y: 3 / 1;
 */

double determinant(double a, double b, double c, double d) {
    return a * d - b * c;
}

bool validator(Point pa, Point pb, Point pc) {
    double a = getLength(pa, pb);
    double b = getLength(pb, pc);
    double c = getLength(pc, pa);

    if ((a + b) > c && (b + c) > a && (c + a) > b) {
        return true;
    } else {
        return false;
    }
}

int getTriangles() {
    int size = points.size();

    if (size < 3) {
        cout << "There is less than 3 points!" << endl;
        return size;
    }

    for (int i = 0; i < size - 2; i++) {
        for (int j = i + 1; j < size - 1; j++) {
            for (int k = j + 1; k < size; k++) {
                if (validator(points[i], points[j], points[k]) == true) {
                    Triangle triangle(points[i], points[j], points[k]);
                    triangles.push_back(triangle);
                }
            }
        }
    }

    return size;
}
