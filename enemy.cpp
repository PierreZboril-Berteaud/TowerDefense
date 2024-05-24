#include "enemy.h"

Enemy::Enemy(){
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QPixmap enemyPixmap("images/enemy.png");

    width = enemyPixmap.width();
    height = enemyPixmap.height();
    setRect(0, 0, width, height);
    setPen(Qt::NoPen);
    PV =20;
    dead = false;
    damage = 10;

    enemyPixmapItem = new QGraphicsPixmapItem(enemyPixmap, this);



    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(100);

}

Enemy::~Enemy() {}

void Enemy::move() {
    qreal newX = x();
    qreal newY = y();

        if (newX < 430) {
            newX += 10; 
        }
            // Avance sur axe Y quand x=450 de y=440 à y =145
        else if (newY > 160 && newX<=430){
            newY -= 10;

        }
            // Avance sur axe X de 450 à x=600
        else if (newX < 620 && newY <=160) {
            newX += 10;

        }
            // Descend sur axe Y de Y=145 à y=640
        else if (newY < 660 && newX <=620) {
            newY += 10;

        }
            // Avance sur axe X de X = 600 à x= 1000
        else if (newX < 1020 && newY<=660) {
            newX += 10; 
        }
            // Monte sur axe Y de y=640 à y=440
        else if (newY > 460 && newX<=1020) {
            newY -= 10; 
        }
            // AVANCE DE X=1000 à x=1880
        else if (newX < 1820 && newY>=460) {
            newX += 10; 
        }
            // Arrête le déplacement lorsque l'ennemi atteint la destination
        else {
            qDebug() << "Enemy reached the end";
            emit reachedEnd();

            remove_enemy();
            return;
        }
        // Met à jour la position de l'ennemi
        setPos(newX, newY);
        //qDebug()<<this->pos();

}

QRectF Enemy::boundingRect() const {
    return QRectF(0, 0, rect().width(), rect().height());
}

void Enemy::remove_enemy() {
    if (move_timer) {
        move_timer->stop();
        delete move_timer;
        move_timer = nullptr;
    }
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
        this->PV = 0;
    }
}

void Enemy::inflict_damage(int damage) {
    qDebug()<<"Enemy take damage";
    if(get_pv()>0) {
        set_pv(PV - damage);
    }
    else{
        if(get_pv()<=0){
            dead = true;
            qDebug() << "Enemy defeated!";
            emit increase_score();

            remove_enemy();
        }
    }
}