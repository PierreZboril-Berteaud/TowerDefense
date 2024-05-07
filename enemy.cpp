
#include "enemy.h"

Enemy::Enemy(){
    setRect(0, 0, 50, 50); // Définir les dimensions du rectangle Enemy
    setPos(0,0);
    QGraphicsTextItem *textItem = new QGraphicsTextItem("Enemy", this);
    textItem->setPos(5, 5);

    // Créer un timer pour gérer le mouvement de l'Enemy
    connect(move_timer, SIGNAL(timeout()),this,SLOT(move()));// Mouvement toutes les 30 millisecondes
    move_timer->start(150);
}
Enemy::~Enemy() {
    delete move_timer;
}

void Enemy::move() {
    setPos(x() + 10, y()); // Déplace l'ennemi d'un pixel vers la droite à chaque intervalle de temps
}

bool Enemy::is_dead(){
    if(get_pv() <= 0){
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
void Enemy::set_dead(bool dead){
    this->dead = dead;
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

void Enemy::inflict_damage(int damage){
    set_pv(PV-damage);
}
void Enemy::remove_enemy(){
    if(x()>500){
        move_timer->stop();
        scene()->removeItem(this);
    }
}