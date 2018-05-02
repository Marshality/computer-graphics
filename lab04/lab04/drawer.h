#ifndef DRAWER_H
#define DRAWER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

class Drawer: public QGraphicsItem
{
public:
    int x = 0;
    int y = 0;
    QPen color = QPen(Qt::black);

    QRectF boundingRect() const
    {
        return QRectF(0, 0, 0, 0);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option) Q_UNUSED(widget);
        painter->setPen(color);
        painter->drawPoint(x, y);
    }
};

#endif // DRAWER_H
