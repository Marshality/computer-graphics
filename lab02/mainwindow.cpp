#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExp values("[-]{0,1}[0-9]{1,5}[.]{0,1}[0-9]{0,4}");
    ui->dx_input->setValidator(new QRegExpValidator(values, this));
    ui->dy_input->setValidator(new QRegExpValidator(values, this));

    ui->xm_input->setValidator(new QRegExpValidator(values, this));
    ui->ym_input->setValidator(new QRegExpValidator(values, this));
    ui->kx_input->setValidator(new QRegExpValidator(values, this));
    ui->ky_input->setValidator(new QRegExpValidator(values, this));

    ui->xc_input->setValidator(new QRegExpValidator(values, this));
    ui->yc_input->setValidator(new QRegExpValidator(values, this));
    ui->angle_input->setValidator(new QRegExpValidator(values, this));

    ui->moveButton->setEnabled(false);
    ui->scaleButton->setEnabled(false);
    ui->rotateButton->setEnabled(false);

    connect(ui->dx_input, SIGNAL(textChanged(QString)), this, SLOT(moveButtonStatus()));
    connect(ui->dy_input, SIGNAL(textChanged(QString)), this, SLOT(moveButtonStatus()));

    connect(ui->xm_input, SIGNAL(textChanged(QString)), this, SLOT(scaleButtonStatus()));
    connect(ui->ym_input, SIGNAL(textChanged(QString)), this, SLOT(scaleButtonStatus()));
    connect(ui->kx_input, SIGNAL(textChanged(QString)), this, SLOT(scaleButtonStatus()));
    connect(ui->ky_input, SIGNAL(textChanged(QString)), this, SLOT(scaleButtonStatus()));

    connect(ui->xc_input, SIGNAL(textChanged(QString)), this, SLOT(rotateButtonStatus()));
    connect(ui->yc_input, SIGNAL(textChanged(QString)), this, SLOT(rotateButtonStatus()));
    connect(ui->angle_input, SIGNAL(textChanged(QString)), this, SLOT(rotateButtonStatus()));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveButtonStatus() {
    ui->moveButton->setEnabled(!(ui->dx_input->text().isEmpty()) && !(ui->dy_input->text().isEmpty()));
}

void MainWindow::scaleButtonStatus() {
    ui->scaleButton->setEnabled(!(ui->xm_input->text().isEmpty()) && !(ui->ym_input->text().isEmpty()) && \
                                !(ui->kx_input->text().isEmpty()) && !(ui->ky_input->text().isEmpty()));
}

void MainWindow::rotateButtonStatus() {
    ui->rotateButton->setEnabled(!(ui->xc_input->text().isEmpty()) && !(ui->yc_input->text().isEmpty()) && \
                                !(ui->angle_input->text().isEmpty()));
}

void MainWindow::on_startButton_clicked()
{
    createAstroid();
    createCube();

    scene->clear();
    draw(scene);

    scene->update();
}

void MainWindow::on_moveButton_clicked()
{
    double dx = ui->dx_input->text().toDouble();
    double dy = ui->dy_input->text().toDouble();

    moveFunction(dx, dy);

    scene->clear();
    draw(scene);
}

void MainWindow::on_scaleButton_clicked()
{
    double xm = ui->xm_input->text().toDouble();
    double ym = ui->ym_input->text().toDouble();
    double kx = ui->kx_input->text().toDouble();
    double ky = ui->ky_input->text().toDouble();

    scaleFunction(xm, ym, kx, ky);

    scene->clear();
    draw(scene);
}

void MainWindow::on_rotateButton_clicked()
{
    double xc = ui->xc_input->text().toDouble();
    double yc = ui->yc_input->text().toDouble();
    double angle = ui->angle_input->text().toDouble();

    rotateFunction(xc, yc, angle);

    scene->clear();
    draw(scene);
}
