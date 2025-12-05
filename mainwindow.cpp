#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setSceneRect(0,0,ui->graphicsView->width()-5,ui->graphicsView->height()-5);
    ui->graphicsView->setScene(scene);
    //setMap();
    connect(ui->graphicsView, &MyQGraphicsView::presPos, this, &MainWindow::addCoor);
}

void MainWindow::setMap(){
    for(int i=0; i<800-blockW; i+=blockW){
        for(int q=0; q<600-blockH; q+=blockH){
            scene->addRect(i, q, blockW, blockH);
        }
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
        scene->removeItem(brickMap.take(position));
        brickMap.remove(position);
    }
}

void MainWindow::saveMap(QHash<QPoint, BrickItem*> map)
{
    QHash<QPoint, TypeObject> myMap;
    for(QPoint point : map.keys()){
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


// Определение функции qHash для использования QPoint в QHash
uint qHash(const QPoint &point, uint seed = 0) {
     return qHash(point.x(), seed) ^ qHash(point.y(), seed); // Используем хеширование координат
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_saveAction_triggered()
{
    saveMap(brickMap);
}


void MainWindow::on_readAction_triggered()
{
    readFile();
}

