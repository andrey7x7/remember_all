#include "myqgraphicsview.h"


MyQGraphicsView::MyQGraphicsView(QWidget* parent)
    : QGraphicsView(parent) // Вызов конструктора базового класса
{
    // Дополнительные настройки кастомного вида
    setDragMode(QGraphicsView::ScrollHandDrag); // Пример настройки
    setCursor(Qt::ArrowCursor);
}

void MyQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    emit presPos(event->pos());
    QGraphicsView::mousePressEvent(event); // Вызвать родительскую функцию для дальнейшей обработки
}
