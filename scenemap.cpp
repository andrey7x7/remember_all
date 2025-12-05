#include "scenemap.h"
#include "QDebug"
#include "QTransform"
#include "QGraphicsSceneMouseEvent"

SceneMap::SceneMap(QObject *parent)
    : QGraphicsScene{parent}
{

}

void SceneMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem *item = itemAt(event->pos(), QTransform());    // Обработка нажатия на элемент
    //qDebug() << item;
    //qDebug() << "Нажатие на элемент:" << event->pos();//.rx() << event->pos().ry();
    QGraphicsScene::mousePressEvent(event); // Вызвать родительскую функцию для дальнейшей обработки
}
