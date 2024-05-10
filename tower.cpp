#include "tower.h"
#include <QGraphicsScene>
#include <QPainter>


Tower::Tower(QGraphicsItem *parent): QGraphicsItem(parent){
    cost = 10;
    range = 10;
    tower_damage = 10;


}

Tower::~Tower() {
    delete timer;
}

QRectF Tower::boundingRect() const {
    // Define the tower's bounding rectangle
    return QRectF(-20, -20, 40, 40);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Draw the tower's graphics
    painter->drawRect(boundingRect());
}
