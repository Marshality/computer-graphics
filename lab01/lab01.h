#ifndef LAB01_H
#define LAB01_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class lab01;
}

class lab01 : public QMainWindow
{
    Q_OBJECT

public:
    explicit lab01(QWidget *parent = 0);
    ~lab01();

private slots:
    void addButtonStatus();

    void delButtonStatus();

    void clrButtonStatus();

    void on_add_button_clicked();

    void on_delete_button_clicked();

    void on_clearButton_clicked();

    void on_taskButton_clicked();

private:
    Ui::lab01 *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
};

#endif // LAB01_H
