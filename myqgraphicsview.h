#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyQGraphicsView(QWidget* parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void presPos(QPoint pos);
};

#endif // MYQGRAPHICSVIEW_H
