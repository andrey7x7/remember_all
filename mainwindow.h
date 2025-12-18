#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QHash>
#include <QFile>
#include <QDataStream>
#include <QTimer>
#include "objectItem.h"
#include "typeenums.h"
#include "myqgraphicsview.h"
#include "brickitem.h"
#include "heroitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer timerCollides;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QHash<QPoint, ObjectItem*> brickMap;
    int blockW = 64;
    int blockH = 64;
    int width = 800;
    int heigh = 600;
    bool press;
    HeroItem *hero;
    TypeEnums::TypeObject type;


public slots:
    void clearMap();
    void setMap();
    void addCoor(QPoint pos);
    void saveMap();
    void readFile();
    void pressPos();
    void releasePos();
    void movePos(QPoint pos);
    void typeObject(TypeEnums::TypeObject type);
    void searchCollides();

protected:
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
