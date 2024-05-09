#include "enemy.h"
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>
Enemy::Enemy() {
    QString path = QDir::currentPath();
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QPixmap enemyPixmap(path + "/images/1.png");
    enemyPixmapItem = new QGraphicsPixmapItem(enemyPixmap, this);
    enemyPixmapItem->setPos(-1000, 0);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(150);

}

Enemy::~Enemy() {
    delete move_timer;
}
int Enemy::get_spawnX(){
    return spawnX;
}
int Enemy::get_spawnY(){
    return spawnY;
}
void Enemy::move() {
    setPos(x() + 10, y());
    if (x() > 1280) {
        remove_enemy();
    }
}

void Enemy::remove_enemy() {
    move_timer->stop();
    scene()->removeItem(this);
    delete this;
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

void Enemy::inflict_damage(int damage) {
    set_pv(PV - damage);
}