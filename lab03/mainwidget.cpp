#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "algorithms.h"

mainwidget::mainwidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwidget)
{
    ui->setupUi(this);

    image = new QImage(651, 621, QImage::Format_ARGB32);

    scene = new QGraphicsScene();

    scene->addPixmap(QPixmap::fromImage(*image));

    ui->graphicsView->setScene(scene);

    //ui->graphicsView->centerOn(0, 0);
    //ui->graphicsView->scene()->setSceneRect(-1000, -1000, 2000, 2000);
    //ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    image->fill(Qt::red);
    image->setPixel(1, 1, my_pen.color().rgb());
}

void mainwidget::on_lineBtn_clicked()
{
    double x1 = ui->x1_input->text().toDouble();
    double x2 = ui->x2_input->text().toDouble();
    double y1 = ui->y1_input->text().toDouble();
    double y2 = ui->y2_input->text().toDouble();

    if (ui->stdFlag->isChecked()) {
        scene->addLine(x1, -y1, x2, -y2, my_pen);
    } else if (ui->ddaFlag->isChecked()) {
        DDA_line(scene, x1, -y1, x2, -y2, my_pen);
    } else if (ui->brFFlag->isChecked()) {
        BREZ_float(scene, x1, -y1, x2, -y2, my_pen);
    } else if (ui->brIntFlag->isChecked()) {
        BREZ_int(scene, x1, -y1, x2, -y2, my_pen);
    }
}
