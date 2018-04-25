#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "algorithms.h"
#include <math.h>

#define WIDTH 1000
#define HEIGHT 1000

#define PI 3.1415926535

mainwidget::mainwidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwidget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    ui->graphicsView->centerOn(0, 0);
    ui->graphicsView->scene()->setSceneRect(-WIDTH, -HEIGHT, WIDTH * 2, HEIGHT * 2);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

mainwidget::~mainwidget()
{
    delete ui;
}

void mainwidget::on_bgColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Background color", QColorDialog::DontUseNativeDialog);
    QGraphicsScene *tmp = new QGraphicsScene();
    ui->bgView->setScene(tmp);
    ui->bgView->setBackgroundBrush(color);
    ui->graphicsView->setBackgroundBrush(color);
}

void mainwidget::on_lineColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Background color", QColorDialog::DontUseNativeDialog);
    QGraphicsScene *tmp = new QGraphicsScene();
    ui->lineView->setScene(tmp);
    ui->lineView->setBackgroundBrush(color);
    my_pen = color;
}

void mainwidget::on_clearBtn_clicked()
{
    scene->clear();
    scene->update();
}

void mainwidget::on_lineBtn_clicked()
{
    double x1 = ui->x1_input->text().toDouble();
    double x2 = ui->x2_input->text().toDouble();
    double y1 = ui->y1_input->text().toDouble();
    double y2 = ui->y2_input->text().toDouble();

    if (ui->stdFlag->isChecked()) {
        scene->addLine(x1, y1, x2, y2, my_pen);
    } else if (ui->ddaFlag->isChecked()) {
        DDA_line(scene, x1, y1, x2, y2, my_pen);
    } else if (ui->brFFlag->isChecked()) {
        BREZ_float(scene, x1, y1, x2, y2, my_pen);
    } else if (ui->brIntFlag->isChecked()) {
        BREZ_int(scene, x1, y1, x2, y2, my_pen);
    } else if (ui->brSFlag->isChecked()) {
        BREZ_smooth(scene, x1, y1, x2, y2, my_pen);
    }
}

void mainwidget::on_sunBtn_clicked()
{
    double d = ui->d_input->text().toDouble();
    double h = ui->h_input->text().toDouble();

    double new_x, new_y;

    for (int i = 0; i < 360; i += h) {
        new_x = cos(i * PI / 180) * d;
        new_y = sin(i * PI / 180) * d;

        if (ui->stdFlag->isChecked()) {
            scene->addLine(0, 0, new_x, new_y, my_pen);
        } else if (ui->ddaFlag->isChecked()) {
            DDA_line(scene, 0, 0, new_x, new_y, my_pen);
        } else if (ui->brFFlag->isChecked()) {
            BREZ_float(scene, 0, 0, new_x, new_y, my_pen);
        } else if (ui->brIntFlag->isChecked()) {
            BREZ_int(scene, 0, 0, new_x, new_y, my_pen);
        } else if (ui->brSFlag->isChecked()) {
            BREZ_smooth(scene, 0, 0, new_x, new_y, my_pen);
        }
    }
}
