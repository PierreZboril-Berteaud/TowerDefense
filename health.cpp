#include "health.h"
#include <QDebug>
#include <iostream>
Health::Health(QGraphicsItem* parent): QGraphicsTextItem(parent){
    health=100;
    setPlainText(QString("PV: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}
void Health::decrease_pv(){
    health = health - 10;
    qDebug()<<"Health decreased : "<<health;
    if (health < 0) {
        health = 0;
        emit gameOver();

    }
    setPlainText(QString("PV: ")+QString::number(health));
}
Health::~Health(){}