#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QColorDialog>
#include <QGraphicsScene>
#include <QImage>

namespace Ui {
class mainwidget;
}

class mainwidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwidget(QWidget *parent = 0);
    ~mainwidget();

private slots:
    void on_bgColor_clicked();

    void on_lineColor_clicked();

    void on_clearBtn_clicked();

    void on_lineBtn_clicked();

    void on_sunBtn_clicked();

private:
    Ui::mainwidget *ui;
    QGraphicsScene *scene;
    QPen my_pen;
    QImage image;
};

#endif // MAINWIDGET_H
