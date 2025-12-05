#ifndef BRICKITEM_H
#define BRICKITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QDataStream>
#include <QDebug>

class BrickItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    BrickItem(int width,int heigh);

private:
    int width;
    int heigh;
    QRectF boundingRect() const{

        return QRectF (0,0,width,heigh);
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::red);

        painter->drawRect(0,0,width,heigh);
        Q_UNUSED(option);
        Q_UNUSED(widget);
    };

};

#endif // BRICKITEM_H
