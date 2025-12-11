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

    this->width = ui->graphicsView->width();
    this->heigh = ui->graphicsView->height();

    connect(ui->graphicsView, &MyQGraphicsView::presPos, this, &MainWindow::addCoor);
    connect(ui->graphicsView, &MyQGraphicsView::presPos, this, &MainWindow::pressPos);
    connect(ui->graphicsView, &MyQGraphicsView::releasePos, this, &MainWindow::releasePos);
    connect(ui->graphicsView, &MyQGraphicsView::movePos, this, &MainWindow::movePos);

    connect(ui->mapOn, &QAction::triggered, this, &MainWindow::setMap);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveMap);
    connect(ui->readAction, &QAction::triggered, this, &MainWindow::readFile);
    connect(ui->clear, &QAction::triggered, this, &MainWindow::clearMap);
//[=](bool force=true){ keepTrack(force); }
    connect(ui->brick, &QAction::triggered, this, [=](TypeEnums::TypeObject force=TypeEnums::TypeObject::Brick) {typeObject(force);});
    connect(ui->road, &QAction::triggered, this, [=](TypeEnums::TypeObject force=TypeEnums::TypeObject::Road) {typeObject(force);});
    connect(ui->spruce, &QAction::triggered, this, [=](TypeEnums::TypeObject force=TypeEnums::TypeObject::Spruce) {typeObject(force);});
    connect(ui->jug, &QAction::triggered, this, [=](TypeEnums::TypeObject force=TypeEnums::TypeObject::Jug) {typeObject(force);});
}

// Определение функции qHash для использования QPoint в QHash
uint qHash(const QPoint &point, uint seed = 0) {
     return qHash(point.x(), seed) ^ qHash(point.y(), seed); // Используем хеширование координат
}

void MainWindow::setMap(){
    for(int i=0; i<width-blockW; i+=blockW){
        for(int q=0; q<heigh-blockH; q+=blockH){
            scene->addRect(i, q, blockW, blockH);
        }
    }
}

void MainWindow::typeObject(TypeEnums::TypeObject type)
{
    ui->brick->setChecked(false);
    ui->road->setChecked(false);
    ui->spruce->setChecked(false);
    ui->jug->setChecked(false);
    this->type=type;
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
        BrickItem *brick = new BrickItem(type,blockW,blockH);
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
    QHash<QPoint, TypeEnums::TypeObject> myMap;
    for(QPoint point : brickMap.keys()){
        myMap.insert(point, TypeEnums::TypeObject::Brick);
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
    QHash<QPoint, TypeEnums::TypeObject> loadedHash;
    QFile fileIn("hash.dat");
    if (fileIn.open(QIODevice::ReadOnly)) {
        QDataStream in(&fileIn);
        in >> loadedHash; // Десериализуем QHash
        loadedHash.insert(QPoint(0,0),TypeEnums::TypeObject::Hero);
        fileIn.close();
        ui->statusbar->showMessage("Карта загружена из hash.dat", 10000);
        qDebug() << "Loaded hash:" << loadedHash;
        for(QPoint point : loadedHash.keys()){
            if(loadedHash.value(point) == TypeEnums::TypeObject::Brick){
                BrickItem *brick = new BrickItem(loadedHash.value(point),blockW,blockH);
                brick->setPos(point);
                brickMap.insert(point, brick);
                scene->addItem(brick);
            }
            if(loadedHash.value(point) == TypeEnums::TypeObject::Hero){
                hero = new HeroItem(blockW,blockH);
                hero->setPos(point);
                brickMap.insert(point, hero);
                scene->addItem(hero);
            }
        }
    } else {
        qDebug() << "Error opening file for reading";
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    hero->keyPress(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}


