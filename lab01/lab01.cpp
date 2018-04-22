#include "lab01.h"
#include "ui_lab01.h"
#include "settings.h"
#include <iostream>
#include "functions.h"
#include <QMessageBox>

using namespace std;

lab01::lab01(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lab01)
{
    ui->setupUi(this);

    QRegExp values("[-]{0,1}[0-9]{1,5}[.]{0,1}[0-9]{0,4}");
    ui->x_lineEdit->setValidator(new QRegExpValidator(values, this));
    ui->y_lineEdit->setValidator(new QRegExpValidator(values, this));

    ui->add_button->setEnabled(false);
    ui->delete_button->setEnabled(false);
    ui->clearButton->setEnabled(false);

    connect(ui->x_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(addButtonStatus()));
    connect(ui->y_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(addButtonStatus()));
    connect(ui->pointsList, SIGNAL(itemSelectionChanged()), this, SLOT(delButtonStatus()));
    connect(ui->pointsList, SIGNAL(itemSelectionChanged()), this, SLOT(clrButtonStatus()));

    scene = new QGraphicsScene(this);
    ui->graphwin->setScene(scene);
}

lab01::~lab01()
{
    delete ui;
}

void lab01::clrButtonStatus() {
    ui->clearButton->setEnabled(points.size() > 0);
}

void lab01::delButtonStatus() {
    ui->delete_button->setEnabled(ui->pointsList->currentRow() >= 0);
}

void lab01::addButtonStatus() {
    ui->add_button->setEnabled(!(ui->x_lineEdit->text().isEmpty()) && !(ui->y_lineEdit->text().isEmpty()));
}

void lab01::on_add_button_clicked()
{
    scene->update();

    double x_value = ui->x_lineEdit->text().toDouble();
    double y_value = ui->y_lineEdit->text().toDouble();

    Point point(x_value, y_value);
    points.push_back(point);

    cout << "Array" << endl;
    for (auto i = points.begin(); i < points.end(); i++)
        i->coord();

    QString coordinates = "x: " + ui->x_lineEdit->displayText() + "  y: " + ui->y_lineEdit->displayText();
    ui->pointsList->addItem(coordinates);

    point.draw(scene);
}

void lab01::on_delete_button_clicked()
{
    int index = ui->pointsList->currentRow();

    points.erase(points.begin() + index);

    ui->pointsList->currentItem()->~QListWidgetItem();
    int size = points.size();
    cout << size << endl;

    scene->clear();

    for (auto iterator = points.begin(); iterator < points.end(); iterator++) {
        iterator->draw(scene);
    }

    if (size == 0) {
        scene->clear();
    }
}

void lab01::on_clearButton_clicked()
{
    scene = new QGraphicsScene(this);
    ui->graphwin->setScene(scene);

    triangles.clear();
    points.clear();

    ui->triangleInfo->clear();
    ui->pointsList->clear();

    scene->update();
}

void lab01::on_taskButton_clicked()
{
    scene->clear();
    triangles.clear();
    ui->triangleInfo->clear();

    int check = getTriangles();
    int size = triangles.size();

    if (check < 3) {
        QMessageBox::warning(this, "Error!", "Для построения треугольника необходимо больше точек.");

        for (auto iterator = points.begin(); iterator < points.end(); iterator++) {
            iterator->draw(scene);
        }
    } else if (size == 0) {
        QMessageBox::warning(this, "Error!", "Нет существующих треугольников!");
        for (auto iterator = points.begin(); iterator < points.end(); iterator++) {
            iterator->draw(scene);
        }
    } else {
        for (auto iterator = points.begin(); iterator < points.end(); iterator++) {
            iterator->draw(scene);
        }

        double theHeight = -1;
        int flag = -1;

        for (int iterator = 0; iterator < size; iterator++) {
            if (triangles[iterator].maxHeight > theHeight) {
                theHeight = triangles[iterator].maxHeight;
                flag = iterator;
            }
        }

        QString coordinates;
        coordinates.sprintf("x: %.3f y: %.3f", (triangles.begin() + flag)->pa.x, (triangles.begin() + flag)->pa.y);
        ui->triangleInfo->addItem(coordinates);
        coordinates.sprintf("x: %.3f y: %.3f", (triangles.begin() + flag)->pb.x, (triangles.begin() + flag)->pb.y);
        ui->triangleInfo->addItem(coordinates);
        coordinates.sprintf("x: %.3f y: %.3f", (triangles.begin() + flag)->pc.x, (triangles.begin() + flag)->pc.y);
        ui->triangleInfo->addItem(coordinates);
        coordinates.sprintf("x: %.3f y: %.3f", (triangles.begin() + flag)->heights[(triangles.begin() + flag)->findMaxHeight()].crossing.x, \
                                           (triangles.begin() + flag)->heights[(triangles.begin() + flag)->findMaxHeight()].crossing.y);
        ui->triangleInfo->addItem(coordinates);

        QColor red(Qt::red);
        ui->triangleInfo->item(3)->setTextColor(red);

        (triangles.begin() + flag)->draw(scene);

        QString answer;
        answer.sprintf("Найденная высота: %.3f", (triangles.begin() + flag)->maxHeight);
        QMessageBox::information(this, "Ответ", answer);
    }
}
