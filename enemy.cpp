
#include "enemy.h"

Enemy::Enemy(){
    setRect(0, 0, 50, 50); // Définir les dimensions du rectangle Enemy

    // Créer un timer pour gérer le mouvement de l'Enemy
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Enemy::move);// Mouvement toutes les 30 millisecondes
    timer->start(30);
}
Enemy::~Enemy() {
    delete timer;
}

void Enemy::move(){
    setPos(x()+2,y()); //Bouge l'enemy sur le coté vers la droite
    if(pos().x() + rect().height()>800){
        scene()->removeItem(this);
        delete this;
    }
}

bool Enemy::is_dead(){
    if(get_pv() == 0){
        return true;
    }
    else{
        return false;
    }
}
int Enemy::get_pv(){
    return PV;
}
int Enemy::get_damage(){
    return damage;
}

void Enemy::set_damage(int damage){
    if(damage>0){
        this->damage = damage;
    }
    else{
        std::cout<<"Les dégats doivent être supérieurs à 0";
    }
}
void Enemy::set_pv(int PV){
    if(PV>0){
        this->PV = PV;
    }
    else{
        std::cout<<"Les PV doivent êtres supérieurs à 0";
    }
}
