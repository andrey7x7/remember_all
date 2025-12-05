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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum TypeObject {
        Brick,
        Tree,
        Food
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QHash<QPoint, BrickItem*> brickMap;
    int blockW = 16;
    int blockH = 16;
    bool press;

public slots:
    void clearMap();
    void setMap();
    void addCoor(QPoint pos);
    void saveMap();
    void readFile();
    void pressPos();
    void releasePos();
    void movePos(QPoint pos);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
