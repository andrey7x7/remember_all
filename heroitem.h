#ifndef HEROITEM_H
#define HEROITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

class HeroItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    HeroItem(int width,int heigh);

private:
    int width;
    int heigh;
    int stepX;
    int stepY;
    QTimer timer_step;

    QRectF boundingRect() const{

        return QRectF (0,0,width,heigh);
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::green);

        painter->drawRect(0,0,width,heigh);
        Q_UNUSED(option);
        Q_UNUSED(widget);
    };

public slots:
    void keyPress(QKeyEvent *event);

private  slots:
    void stepTimer();

};

#endif // HEROITEM_H
