#include "lab01.h"
#include <QApplication>
#include "point.h"
#include "triangle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lab01 w;
    w.show();

    return a.exec();
}
