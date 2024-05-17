#include "enemy.h"

Enemy::Enemy(){
    QString path = QDir::currentPath();
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QPixmap enemyPixmap(path + "/images/1.png");

    PV =100;
    dead = false;
    damage = 10;

    enemyPixmapItem = new QGraphicsPixmapItem(enemyPixmap, this);
    enemyPixmapItem->setPos(0,450);


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
    qreal newX = x();
    qreal newY = y();

    // Avance sur axe X de X = 0 jusqu'à x = 450
    while (newX < 450) {
        newX += 10; // ou toute autre valeur de déplacement souhaitée
        setPos(newX, newY);
        // Ajoutez un délai ici si vous voulez une animation plus lente
    }

    // Avance sur axe Y quand x=450 de y=440 à y =145
    while (newY > 145) {
        newY -= 10; // ou toute autre valeur de déplacement souhaitée
        setPos(newX, newY);
        // Ajoutez un délai ici si vous voulez une animation plus lente
    }

    // Avance sur axe X de 450 à x=600
    while (newX < 600) {
        newX += 10; // ou toute autre valeur de déplacement souhaitée
        setPos(newX, newY);
        // Ajoutez un délai ici si vous voulez une animation plus lente
    }

    // Descend sur axe Y de Y=145 à y=640
    while (newY < 640) {
        newY += 10; // ou toute autre valeur de déplacement souhaitée
        setPos(newX, newY);
        // Ajoutez un délai ici si vous voulez une animation plus lente
    }

    // Avance sur axe X de X = 600 à x= 1000
    while (newX < 1000) {
        newX += 10; // ou toute autre valeur de déplacement souhaitée
        setPos(newX, newY);
        // Ajoutez un délai ici si vous voulez une animation plus lente
    }

    // Monte sur axe Y de y=640 à y=440
    while (newY > 440) {
        newY -= 10; // ou toute autre valeur de déplacement souhaitée
        setPos(newX, newY);
        // Ajoutez un délai ici si vous voulez une animation plus lente
    }

    // AVANCE DE X=1000 à x=1880
    while (newX < 1880) {
        newX += 10; // ou toute autre valeur de déplacement souhaitée
        setPos(newX, newY);
        // Ajoutez un délai ici si vous voulez une animation plus lente
    }
}

void Enemy::remove_enemy() {
    move_timer->stop();
    scene()->removeItem(this);
    delete this;
}

bool Enemy::is_dead(){
    return dead;
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