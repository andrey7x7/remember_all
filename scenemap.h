#ifndef SCENEMAP_H
#define SCENEMAP_H

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

class SceneMap : public QGraphicsScene
{
    Q_OBJECT
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:
    explicit SceneMap(QObject *parent = nullptr);
};

#endif // SCENEMAP_H
