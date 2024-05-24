#include "enemy.h"
#include "tower.h"
#include <QGraphicsItemGroup>



Tower::Tower(){
    QPixmap towerTexture("images/tower.png");


    QGraphicsRectItem* tower_rect = new QGraphicsRectItem(-25, -30, 50, 60, this); // Position et taille du rectangle
    tower_rect->setPen(QPen(Qt::transparent)); // Définit le contour en rouge
    QGraphicsPixmapItem* tower_texture_item = new QGraphicsPixmapItem(towerTexture, tower_rect);
    tower_texture_item->setOffset(-25, -30); // Positionner la texture sur le rectangle

    damage=10;
    attack_range = 250; // portée de la tour
    cost = 25;
    range_indicator = new QGraphicsEllipseItem(-attack_range, -attack_range, attack_range * 2, attack_range * 2, this);
    range_indicator->setPen(QPen(Qt::black)); // Rend la bordure de couleur noire
    range_indicator->setOpacity(0.3); // Opacité réduite pour l'indicateur de portée


    // Crée un timer pour l'attaque de la tour
    QTimer* attack_timer = new QTimer(this);
    connect(attack_timer, &QTimer::timeout, this, &Tower::tower_fire);
    attack_timer->start(2500); // Démarre le timer avec une intervalle de 1s

}
void Tower::tower_fire(){
    // Recherche tous les items dans la zone d'attaque de la tour
    QList<QGraphicsItem*> colliding_items = range_indicator->collidingItems();
    //qDebug() << "Number of colliding items:" << colliding_items.size();

    // Parcourt tous les items en collision
    for (int i = 0; i < colliding_items.size(); ++i) {
        // Vérifie si l'item en collision est un ennemi
        if (Enemy* enemy = dynamic_cast<Enemy*>(colliding_items[i])) {
            // Inflige des dégâts à l'ennemi
            enemy->inflict_damage(10);
            break;
        }
    }
}
bool Tower::is_valid_place(){

    QRectF NonValidPlace1(0,440, 500, 100);
    QRectF NonValidPlace2(400,140, 100, 300);
    QRectF NonValidPlace3(500,140, 200, 100);
    QRectF NonValidPlace4(600,240, 100, 500);
    QRectF NonValidPlace5(700,640, 400, 100);
    QRectF NonValidPlace6(1000,440, 100, 200);
    QRectF NonValidPlace7(1100,440, 800, 100);
    if(NonValidPlace1.contains(sceneBoundingRect())||NonValidPlace2.contains(sceneBoundingRect())||NonValidPlace3.contains(sceneBoundingRect())||NonValidPlace4.contains(sceneBoundingRect())||NonValidPlace5.contains(sceneBoundingRect())||NonValidPlace6.contains(sceneBoundingRect())||NonValidPlace7.contains(sceneBoundingRect())) {
        return false;
    }
    return true;

}
Tower::~Tower() {
    delete attack_timer;
    delete TowerPixmapItem;
}

