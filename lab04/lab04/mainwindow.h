#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColorDialog>

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
    void on_bgColor_clicked();

    void on_lineColor_clicked();

    void on_clearBtn_clicked();

    void on_drawCBtn_clicked();

    void on_drawCCBtn_clicked();

    void on_drawEBtn_clicked();

    void on_drawECBtn_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPen my_pen;
    QBrush my_brush;
};

#endif // MAINWINDOW_H
