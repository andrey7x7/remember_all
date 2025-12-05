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
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void presPos(QPoint pos);
    void releasePos();
    void movePos(QPoint pos);
};

#endif // MYQGRAPHICSVIEW_H
