#include "brickitem.h"

BrickItem::BrickItem(TypeEnums::TypeObject type, int width, int heigh)
{
    this->width=width;
    this->heigh=heigh;
    this->type=type;
    setCursor(Qt::ArrowCursor);
}

