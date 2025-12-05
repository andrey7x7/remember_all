#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    press = false;
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setSceneRect(0,0,ui->graphicsView->width()-5,ui->graphicsView->height()-5);
    ui->graphicsView->setScene(scene);

    connect(ui->graphicsView, &MyQGraphicsView::presPos, this, &MainWindow::addCoor);
    connect(ui->graphicsView, &MyQGraphicsView::presPos, this, &MainWindow::pressPos);
    connect(ui->graphicsView, &MyQGraphicsView::releasePos, this, &MainWindow::releasePos);
    connect(ui->graphicsView, &MyQGraphicsView::movePos, this, &MainWindow::movePos);

    connect(ui->mapOn, &QAction::triggered, this, &MainWindow::setMap);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveMap);
    connect(ui->readAction, &QAction::triggered, this, &MainWindow::readFile);
    connect(ui->clear, &QAction::triggered, this, &MainWindow::clearMap);
}

// Определение функции qHash для использования QPoint в QHash
uint qHash(const QPoint &point, uint seed = 0) {
     return qHash(point.x(), seed) ^ qHash(point.y(), seed); // Используем хеширование координат
}

void MainWindow::setMap(){
    for(int i=0; i<800-blockW; i+=blockW){
        for(int q=0; q<600-blockH; q+=blockH){
            scene->addRect(i, q, blockW, blockH);
        }
    }
}

void MainWindow::clearMap()
{
    brickMap.clear();
    scene->clear();
}

void MainWindow::pressPos()
{
    press = true;
}

void MainWindow::releasePos()
{
    press = false;
}

void MainWindow::movePos(QPoint pos)
{
    if(press){
        addCoor(pos);
    }
}

void MainWindow::addCoor(QPoint pos){
    QPoint position ((pos.rx()/blockW)*blockW, (pos.ry()/blockW)*blockW);
    if(!brickMap.contains(position)){
        BrickItem *brick = new BrickItem(blockW,blockH);
        brick->setPos(position);
        brickMap.insert(position, brick);
        scene->addItem(brick);
    }
    else{
        if(!press){
            scene->removeItem(brickMap.take(position));
            brickMap.remove(position);
        }
    }
}

void MainWindow::saveMap()
{
    QHash<QPoint, TypeObject> myMap;
    for(QPoint point : brickMap.keys()){
        myMap.insert(point, TypeObject::Brick);
    }
    QFile fileOut("hash.dat");
    if (fileOut.open(QIODevice::WriteOnly)) {
        QDataStream out(&fileOut);
        out << myMap; // Сериализуем QHash
        fileOut.close();
        ui->statusbar->showMessage("Карта сохранена в hash.dat", 10000);
    } else {
        ui->statusbar->showMessage("Ошибка сохранения карты", 10000);
    }
}

void MainWindow::readFile(){
    QHash<QPoint, TypeObject> loadedHash;
    QFile fileIn("hash.dat");
    if (fileIn.open(QIODevice::ReadOnly)) {
        QDataStream in(&fileIn);
        in >> loadedHash; // Десериализуем QHash
        fileIn.close();
        ui->statusbar->showMessage("Карта загружена из hash.dat", 10000);
        qDebug() << "Loaded hash:" << loadedHash;
        for(QPoint point : loadedHash.keys()){
            if(loadedHash.value(point) == TypeObject::Brick){
                BrickItem *brick = new BrickItem(blockW,blockH);
                brick->setPos(point);
                brickMap.insert(point, brick);
                scene->addItem(brick);
            }
        }
    } else {
        qDebug() << "Error opening file for reading";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


