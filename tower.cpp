#include "enemy.h"
#include "tower.h"
#include <QGraphicsItemGroup>



Tower::Tower(qreal x,qreal y,int towerType){
    if(towerType==1){

        QPixmap towerTexture("images/tower_type_1.png");


        towerRect = new QGraphicsRectItem(-15, 90, 50, 60, this);
        towerRect->setPen(QPen(Qt::transparent)); // Définit le contour transparent

        towerTextureItem = new QGraphicsPixmapItem(towerTexture, towerRect);
        towerTextureItem->setOffset(-25, -30); // Positionner la texture sur le rectangle

        this->x = x;
        this->y = y;

        damage = 5;
        attackRange = 250; // portée de la tour
        cost = 35;
        rangeIndicator = new QGraphicsEllipseItem(-attackRange, -attackRange, attackRange * 2, attackRange * 2, towerRect);
        rangeIndicator->setPen(QPen(Qt::black)); // Rend la bordure de couleur noire
        rangeIndicator->setOpacity(0.3); // Opacité réduite pour l'indicateur de portée
        QTimer* attackTimer = new QTimer(this);
        connect(attackTimer, &QTimer::timeout, this, &Tower::towerFire);
        attackTimer->start(1000); // Démarre le timer avec une intervalle de 1s

    }

}
void Tower::towerFire(){
    // Recherche tous les items dans la zone d'attaque de la tour
    QList<QGraphicsItem*> colliding_items = rangeIndicator->collidingItems();

    for (int i = 0; i < colliding_items.size(); ++i) {
        // Vérifie si l'item en collision est un ennemi
        if (Enemy* enemy = dynamic_cast<Enemy*>(colliding_items[i])) {
            Projectile* projectile = new  Projectile(towerGetX(),towerGetY(),enemy);
            scene()->addItem(projectile);

            break;
        }
    }
}
bool Tower::isValidPlace(){

    QRectF NonValidPlace1(0,400, 400, 200);
    QRectF NonValidPlace2(400,100, 100, 500);
    QRectF NonValidPlace3(500,120, 200, 170);
    QRectF NonValidPlace4(600,240, 100, 550);
    QRectF NonValidPlace5(700,600, 400, 180);
    QRectF NonValidPlace6(1000,400, 100, 240);
    QRectF NonValidPlace7(1100,400, 800, 180);
    if(NonValidPlace1.contains(sceneBoundingRect())||NonValidPlace2.contains(sceneBoundingRect())||NonValidPlace3.contains(sceneBoundingRect())||NonValidPlace4.contains(sceneBoundingRect())||NonValidPlace5.contains(sceneBoundingRect())||NonValidPlace6.contains(sceneBoundingRect())||NonValidPlace7.contains(sceneBoundingRect())) {
        return false;
    }
    return true;

}
void Tower::deleteTower(){
    if(attackTimer) {
        attackTimer = nullptr;
        delete attackTimer;
    }
    if(rangeIndicator) {
        rangeIndicator = nullptr;
        delete rangeIndicator;
    }
    if(towerRect) {
        towerRect = nullptr;
        delete towerRect;
    }
    if(towerTextureItem){
        towerTextureItem = nullptr;
        delete towerTextureItem;
    }

    if(TowerPixmapItem){
        TowerPixmapItem = nullptr;
        delete TowerPixmapItem;
    }

}
Tower::~Tower() {}

