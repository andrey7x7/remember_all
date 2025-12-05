#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QHash>
#include <QFile>
#include <QDataStream>
#include "myqgraphicsview.h"
#include "brickitem.h"
#include "heroitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum TypeObject {
        Hero,
        Brick,
        Tree,
        Food
    };

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QHash<QPoint, QGraphicsItem*> brickMap;
    int blockW = 16;
    int blockH = 16;
    bool press;
    HeroItem *hero;


public slots:
    void clearMap();
    void setMap();
    void addCoor(QPoint pos);
    void saveMap();
    void readFile();
    void pressPos();
    void releasePos();
    void movePos(QPoint pos);

protected:
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
