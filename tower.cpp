#include "tower.h"



Tower::Tower(){

    QGraphicsRectItem* towerRect = new QGraphicsRectItem(-25, -30, 50, 60, this); // Position et taille du rectangle
    towerRect->setPen(QPen(Qt::red)); // Définit le contour en rouge

    attack_range = 200;

    // Crée un cercle pour indiquer la portée de l'attaque
    range_indicator = new QGraphicsEllipseItem(-attack_range, -attack_range, attack_range * 2, attack_range * 2, this);
    range_indicator->setPen(QPen(Qt::black)); // Rend la bordure de couleur noire
    range_indicator->setOpacity(0.3); // Opacité réduite pour l'indicateur de portée

    // Crée un timer pour l'attaque de la tour
    QTimer* attack_timer = new QTimer(this);
    connect(attack_timer, &QTimer::timeout, this, &Tower::tower_fire);
    attack_timer->start(1000); // Démarre le timer avec une intervalle de 1000 ms (1 seconde)

}
void Tower::tower_fire(){

}
bool Tower::is_valid_place(){

    QRectF NonValidPlace1(0,440, 500, 100);
    QRectF NonValidPlace2(400,140, 100, 300);
    QRectF NonValidPlace3(500,140, 200, 100);
    QRectF NonValidPlace4(600,240, 100, 500);
    QRectF NonValidPlace5(700,640, 400, 100);
    QRectF NonValidPlace6(1000,440, 100, 200);
    QRectF NonValidPlace7(1100,440, 800, 100);
    if(NonValidPlace1.contains(sceneBoundingRect())){
        return false;
    }
    else{
        if(NonValidPlace2.contains(sceneBoundingRect())){
            return false;
        }
        else{
            if(NonValidPlace3.contains(sceneBoundingRect())){
                return false;
            }
            else{
                if(NonValidPlace4.contains(sceneBoundingRect())){
                    return false;
                }
                else{
                    if(NonValidPlace5.contains(sceneBoundingRect())){
                        return false;
                    }
                    else{
                        if(NonValidPlace6.contains(sceneBoundingRect())){
                            return false;
                        }
                        else{
                            if(NonValidPlace7.contains(sceneBoundingRect())){
                                return false;
                            }
                        }
                    }

                }
            }
        }
    }
    return true;

}
Tower::~Tower() {
    delete attaque_timer;
    delete TowerPixmapItem;
}

