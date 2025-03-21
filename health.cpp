#include "health.h"
#include <QDebug>
Health::Health(QGraphicsItem* parent): QGraphicsTextItem(parent){
    health=100;
    setPlainText(QString("Vie: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}
void Health::decreasePv(int damage){
    health = health - 1000;
    if (health <= 0) {
        health = 0;
        emit gameOver();

    }
    setPlainText(QString("Vie: ")+QString::number(health));
}
Health::~Health(){}