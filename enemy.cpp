#include "enemy.h"

Enemy::Enemy(int enemyType){
    if(enemyType==1) {
        QPixmap enemyPixmap("images/enemy.png");

        width = enemyPixmap.width();
        height = enemyPixmap.height();
        setRect(0, 0, width, height);
        setPen(Qt::NoPen);
        setPv(30);
        setDead(false);
        setDamage(10);

        enemyPixmapItem = new QGraphicsPixmapItem(enemyPixmap, this);

        connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
        moveTimer->start(120);

        setPos(0, 460);

    }
    if(enemyType==2){
        QPixmap enemyPixmap("images/enemy_type_2.png");
        width = enemyPixmap.width();
        height = enemyPixmap.height();
        setRect(0, 0, width, height);
        setPen(Qt::NoPen);
        setPv(50);
        setDead(false);
        setDamage(100);

        enemyPixmapItem = new QGraphicsPixmapItem(enemyPixmap, this);

        connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
        moveTimer->start(150);

        setPos(0, 460);

    }


}



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
            emit reachedEnd(getDamage());
            removeEnemy();
            return;
        }
        // Met à jour la position de l'ennemi
        setPos(newX, newY);

}

QRectF Enemy::boundingRect() const {
    return QRectF(0, 0, rect().width(), rect().height());
}

void Enemy::removeEnemy() {
    if (moveTimer) {
        moveTimer->stop();
        moveTimer = nullptr;
        delete moveTimer;

    }
    scene()->removeItem(this);
}
void Enemy::deleteEnemys(){
        if (moveTimer) {
            moveTimer->stop();
            moveTimer = nullptr;
            delete moveTimer;
        }
        if (enemyPixmapItem) {
            enemyPixmapItem = nullptr;
            delete enemyPixmapItem;
        }
}


void Enemy::inflictDamage(int damage) {

    setPv(PV-damage);

    if(getPv()>0) {
        return;
    }
    else{
        if(getPv()<=0){
            setDead(true);
            emit increaseScore();
            emit addGold();
            removeEnemy();
        }
    }
}
Enemy::~Enemy() {}