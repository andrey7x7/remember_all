#include "brickitem.h"

BrickItem::BrickItem(int width, int heigh)
{
    this->width=width;
    this->heigh=heigh;
    setCursor(Qt::ArrowCursor);
}

