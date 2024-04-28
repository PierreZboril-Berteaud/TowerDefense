#include "tower.h"
#include <QGraphicsScene>
#include "enemy.h"

Tower::Tower(QGraphicsItem *parent) : QObject(), QGraphicsRectItem(parent) {
    setRect(0, 0, 50, 50); // Définit les dimensions du rectangle de la tour
    QGraphicsTextItem *textItem = new QGraphicsTextItem("Tower", this);
    textItem->setPos(5, 5);

    // Création d'un timer pour vérifier les collisions avec les ennemis
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkCollision()));
    timer->start(100); // Vérification toutes les 100 millisecondes
}

Tower::~Tower() {
    delete timer;
}
