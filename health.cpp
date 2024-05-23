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
    qDebug()<<"Health decreased : "<<health;
    health = health - 10;
    if (health < 0) {
        health = 0;
    }
    setPlainText(QString("PV: ")+QString::number(health));
}
Health::~Health(){}