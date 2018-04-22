#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void moveButtonStatus();

    void scaleButtonStatus();

    void rotateButtonStatus();

    void on_startButton_clicked();

    void on_moveButton_clicked();

    void on_scaleButton_clicked();

    void on_rotateButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
