#ifndef TOWERDEFENSE_PROJECTILE_H
#define TOWERDEFENSE_PROJECTILE_H

#include "enemy.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <iostream>
#include <QPixmap>
#include <QCoreApplication>
#include <QVector2D>
#include <QTimer>

class Projectile : public QObject,public QGraphicsRectItem{
    Q_OBJECT
    private :
        Enemy* ptarget;
        float speed;
        qreal height;
        qreal width;

        qreal x;
        qreal y;

        QTimer* ptimer;


    public :
        QGraphicsPixmapItem *ProjectilePixmapItem;
        Projectile(qreal x,qreal y,Enemy* target);
        ~Projectile();

    void updateProjectile();
};


#endif //TOWERDEFENSE_PROJECTILE_H
