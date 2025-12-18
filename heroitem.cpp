#include "heroitem.h"

HeroItem::HeroItem(int width, int heigh)
{
    setCursor(Qt::OpenHandCursor);

    this->width=width-8;
    this->heigh=heigh-8;
    this->setType(TypeEnums::TypeObject::Hero);
    stepX = 0;
    stepY = 0;

    connect(&timer_step,SIGNAL(timeout()),this,SLOT(stepTimer()));
    connect(&timer_frame,SIGNAL(timeout()),this,SLOT(frameTimer()));
    timer_frame.start(200);
    timer_step.start(30);
}

QRectF HeroItem::boundingRect() const{

    return QRectF(0,0,width,heigh);
};

void HeroItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap *spriteImage = new QPixmap(":/sprites/land/sprites/anim_cat.png"); // Загружаем изображение спрайта в QPixmap
    painter->drawPixmap(8, 8, width, heigh, *spriteImage, 106+stepFrame*frame, 33+rowFrame, 128, 128);
    painter->drawRect(QRectF(0,0,width,heigh));
    Q_UNUSED(option);
    Q_UNUSED(widget);
};

void HeroItem::stepTimer()
{
    this->setPos(pos().x()+stepX,pos().y()+stepY);
}

void HeroItem::frameTimer()
{
    if(frame<3){
        frame += 1;
    }
    else{
        frame = 0;
    }
    this->update();
}

void HeroItem::keyPress(QKeyEvent *event)
{
    if (event->key()==Qt::Key_W)
    {
        rowFrame=270;
        direction = TypeEnums::Direction::Up;
        stepX = 0;
        stepY = - 1;
    }
    if (event->key()==Qt::Key_S)
    {
        rowFrame=0;
        direction = TypeEnums::Direction::Down;
        stepX = 0;
        stepY = 1;
    }
    if (event->key()==Qt::Key_A)
    {
        rowFrame=400;
        direction = TypeEnums::Direction::Left;
        stepY = 0;
        stepX = - 1;
    }
    if (event->key()==Qt::Key_D)
    {
        rowFrame=135;
        direction = TypeEnums::Direction::Right;
        stepY = 0;
        stepX = 1;
    }
}

void HeroItem::breackCollides()
{
    stepY = 0;
    stepX = 0;
}
