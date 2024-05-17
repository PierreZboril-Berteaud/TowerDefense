#include "health.h"
Health::Health(QGraphicsItem* parent): QGraphicsTextItem(parent){
    health = 100;
    setPlainText(QString("PV: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}
void Health::decrease_pv(){
    health--;
    setPlainText(QString("PV: ")+QString::number(health));
}
Health::~Health(){}