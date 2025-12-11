#ifndef BRICKITEM_H
#define BRICKITEM_H

#include "objectItem.h"

class BrickItem : public ObjectItem
{
    Q_OBJECT

public:
    BrickItem(TypeEnums::TypeObject type, int width, int heigh);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        QPixmap *spriteImage = new QPixmap(":/sprites/land/sprites/obj.jpeg"); // Загружаем изображение спрайта в QPixmap
        painter->setPen(Qt::black);
        painter->setBrush(Qt::red);

        painter->drawPixmap(0,0, *spriteImage, 0, 160, 32, 32);
        //painter->drawRect(0,0,width,heigh);
        Q_UNUSED(option);
        Q_UNUSED(widget);
    };

};

#endif // BRICKITEM_H
