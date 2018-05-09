#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithms.h"

#define WIDTH 2000
#define HEIGHT 2000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    ui->graphicsView->centerOn(0, 0);
    ui->graphicsView->scene()->setSceneRect(-WIDTH, -HEIGHT, WIDTH * 2, HEIGHT * 2);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bgColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Background color", QColorDialog::DontUseNativeDialog);
    QGraphicsScene *tmp = new QGraphicsScene();
    ui->bgView->setScene(tmp);
    ui->bgView->setBackgroundBrush(color);
    ui->graphicsView->setBackgroundBrush(color);
    my_brush = color;
}

void MainWindow::on_lineColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Background color", QColorDialog::DontUseNativeDialog);
    QGraphicsScene *tmp = new QGraphicsScene();
    ui->lineView->setScene(tmp);
    ui->lineView->setBackgroundBrush(color);
    my_pen = color;
}

void MainWindow::on_clearBtn_clicked()
{
    scene->clear();
    scene->update();
}

void MainWindow::on_drawCBtn_clicked()
{
    double radius = ui->rSpin->value();

    if (ui->canBtn->isChecked()) {
        circleCanon(scene, radius, my_pen);
    } else if (ui->parBtn->isChecked()) {
        circleParam(scene, radius, my_pen);
    } else if (ui->brezBtn->isChecked()) {
        circleBrez(scene, radius, my_pen);
    } else if (ui->midBtn->isChecked()) {
        circleMiddle(scene, radius, my_pen);
    } else if (ui->stdBtn->isChecked()) {
        scene->addEllipse(-radius, -radius, radius * 2, radius * 2, my_pen);
    }
}

void MainWindow::on_drawCCBtn_clicked()
{
    double step = ui->cSSpin->value();
    double count = ui->cQSpin->value();

    for (int i = step; i < step * count + step; i += step) {
        if (ui->canBtn->isChecked()) {
            circleCanon(scene, i, my_pen);
        } else if (ui->parBtn->isChecked()) {
            circleParam(scene, i, my_pen);
        } else if (ui->brezBtn->isChecked()) {
            circleBrez(scene, i, my_pen);
        } else if (ui->midBtn->isChecked()) {
            circleMiddle(scene, i, my_pen);
        } else if (ui->stdBtn->isChecked()) {
            scene->addEllipse(-i, -i, i * 2, i * 2, my_pen);
        }
    }
}

void MainWindow::on_drawEBtn_clicked()
{
    double a = ui->aSpin->value();
    double b = ui->bSpin->value();

    if (ui->canBtn->isChecked()) {
        ellipseCanon(scene, a, b, my_pen);
    } else if (ui->parBtn->isChecked()) {
        ellipseParam(scene, a, b, my_pen);
    } else if (ui->brezBtn->isChecked()) {
        ellipseBrez(scene, a, b, my_pen);
    } else if (ui->midBtn->isChecked()) {
        ellipseMiddle(scene, a, b, my_pen);
    } else if (ui->stdBtn->isChecked()) {
        scene->addEllipse(-b, -a, b * 2, a * 2, my_pen);
    }
}

void MainWindow::on_drawECBtn_clicked()
{
    double step = ui->eSSpin->value();
    double count = ui->eQSpin->value();

    for (int i = step; i < step * count + step; i += step) {
        if (ui->canBtn->isChecked()) {
            ellipseCanon(scene, i * 2, i, my_pen);
        } else if (ui->parBtn->isChecked()) {
            ellipseParam(scene, i * 2, i, my_pen);
        } else if (ui->brezBtn->isChecked()) {
            ellipseBrez(scene, i * 2, i, my_pen);
        } else if (ui->midBtn->isChecked()) {
            ellipseMiddle(scene, i * 2, i, my_pen);
        } else if (ui->stdBtn->isChecked()) {
            scene->addEllipse(-i * 2, -i, i * 4, i * 2, my_pen);
        }
    }
}
