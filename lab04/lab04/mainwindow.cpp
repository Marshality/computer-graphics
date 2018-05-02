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
