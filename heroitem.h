#ifndef HEROITEM_H
#define HEROITEM_H

#include <QTimer>
#include <QKeyEvent>
#include "objectItem.h"

class HeroItem : public ObjectItem
{
    Q_OBJECT
public:
    HeroItem(int width, int heigh);

private:
    int width;
    int heigh;
    int step = 32;
    int stepX;
    int stepY;
    int frame = 0;
    int stepFrame = 137;
    int rowFrame = 0;
    QTimer timer_step;
    QTimer timer_frame;
    TypeEnums::Direction direction = TypeEnums::Direction::Right;

public slots:
    void keyPress(QKeyEvent *event);
    void breackCollides();

private  slots:
    void stepTimer();
    void frameTimer();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

};

#endif // HEROITEM_H
