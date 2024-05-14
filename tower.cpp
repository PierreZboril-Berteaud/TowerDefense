#include "tower.h"



Tower::Tower(){
    QString path = QDir::currentPath();
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QPixmap towerPixmap(path + "/images/redTower.png");
    TowerPixmapItem = new QGraphicsPixmapItem(towerPixmap,this);

    attack_range = 125;
    range_indicator = new QGraphicsEllipseItem(-attack_range+35, -attack_range+45, attack_range * 2, attack_range * 2, this);
    range_indicator->setPen(QPen(Qt::black)); // Rendre la bordure de couleur noir
    range_indicator->setOpacity(0.3);

    QTimer *attaque_timer = new QTimer(this);
    connect(attaque_timer, &QTimer::timeout, this, &Tower::tower_fire);
    attaque_timer->start(1000);

}
void Tower::tower_fire(){
    qDebug()<<"Fire";
}
Tower::~Tower() {
    scene()->removeItem(TowerPixmapItem); // Assurez-vous de retirer l'élément de la scène avant de le supprimer
    delete attaque_timer;
    delete TowerPixmapItem;
}

