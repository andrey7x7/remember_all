#include "heroitem.h"

HeroItem::HeroItem(int width, int heigh)
{
    setCursor(Qt::OpenHandCursor);

    this->width=width;
    this->heigh=heigh;
    this->setType(TypeEnums::TypeObject::Hero);
    stepX = 0;
    stepY = 0;

    connect(&timer_step,SIGNAL(timeout()),this,SLOT(stepTimer()));
    timer_step.start(500);
}

void HeroItem::stepTimer()
{
    setPos(pos().rx()+step*stepX, pos().ry()+step*stepY);
}

void HeroItem::keyPress(QKeyEvent *event)
{
    if (event->key()==Qt::Key_W)
    {
        stepX = 0;
        stepY = - 1;
    }
    if (event->key()==Qt::Key_S)
    {
        stepX = 0;
        stepY = 1;
    }
    if (event->key()==Qt::Key_A)
    {
        stepY = 0;
        stepX = - 1;
    }
    if (event->key()==Qt::Key_D)
    {
        stepY = 0;
        stepX = 1;
    }
}
