#ifndef OBJECTITEM_H
#define OBJECTITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include "typeenums.h"

class ObjectItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

protected:
    int width;
    int heigh;
    TypeEnums::TypeObject type;

private:
    QRectF boundingRect() const{
        return QRectF (0,0,width,heigh);
    };

public:
    TypeEnums::TypeObject getType(){
        return type;
    }

    void setType(TypeEnums::TypeObject newType){
        type = newType;
    }
//    ObjectItem(int width,int heigh, QObject *parent = nullptr){
//        this->width = width;
//        this->heigh = heigh;
//    }

};
#endif // OBJECTITEM_H
