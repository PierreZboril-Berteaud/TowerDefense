#include "projectile.h"
Projectile::Projectile(qreal x,qreal y,Enemy* target){
    QPixmap ProjectilePixmap("images/images2.png");
    ptarget = target;

    width = ProjectilePixmap.width();
    height = ProjectilePixmap.height();
    speed = 0.5;
    this->x = x;
    this->y = y;


    setRect(x, y, width, height);
    setPen(Qt::NoPen);
    ProjectilePixmapItem = new QGraphicsPixmapItem(ProjectilePixmap, this);

    setPos(x, y);

    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &Projectile::updateProjectile);
    ptimer->start(1);
}

Projectile::~Projectile(){};


void Projectile::updateProjectile(){
    // Calculer la direction vers l'ennemi
    QPointF targetPos = ptarget->pos();
    QPointF currentPos = pos();

    float dX = targetPos.x() - currentPos.x();
    float dY = targetPos.y() - currentPos.y();

    // Calculer la distance entre les deux points
    float distance = std::sqrt(dX * dX + dY * dY);


    // Si la distance est suffisamment grande, on déplace le projectile
    if (distance > 1e-3) {
        // Normaliser le vecteur de direction en divisant par la distance
        float dirX = dX / distance;
        float dirY = dY / distance;

        float newX = currentPos.x() + dirX*speed;
        float newY = currentPos.y() + dirY*speed;
        // Déplacer le projectile dans cette direction, en tenant compte de la vitesse
        setPos(newX, newY);
    }

    float collidingMargin = 1.0; //marge de collision "hitbox" pour corriger le manque de précision
    if (distance < collidingMargin) {
        ptarget->inflictDamage(1000);


        scene()->removeItem(this);    // Supprimer le projectile de la scène
        if(ptimer) {
            ptimer->stop();
            ptimer = nullptr;
            delete ptimer;
        }
        delete this;                  // Libérer la mémoire du projectile
        return;
    }
}
