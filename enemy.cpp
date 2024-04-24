
#include "enemy.h"
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
Enemy::Enemy(): QObject(), QGraphicsRectItem(){

    //dessine un rectangle qui sera l'enemy
    setRect(0,0,100,100);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moove()));
    timer->start(50);
}

void Enemy::moove(){
    setPos(x()+2,y()); //Bouge l'enemy sur le coté vers la droite
    if(pos().x() + rect().height()>800){
        scene()->removeItem(this);
        delete this;
    }
}

Enemy::~Enemy(){}