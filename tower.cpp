#include "tower.h"



Tower::Tower(){
    cost = 10;
    range = 10;
    tower_damage = 10;

    QString path = QDir::currentPath();
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QPixmap towerPixmap(path + "/images/redTower.png");
    TowerPixmapItem = new QGraphicsPixmapItem(towerPixmap,this);



}

Tower::~Tower() {
    delete timer;
}

