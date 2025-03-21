#ifndef TOWER_H
#define TOWER_H

#include "projectile.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>


class Tower :public QObject,public QGraphicsRectItem {
    Q_OBJECT
    public:
        QGraphicsPixmapItem *TowerPixmapItem;
        Tower(qreal x,qreal y,int towerType);
        bool isValidPlace();
        virtual ~Tower();
        int getCost(){return cost;}

        qreal towerGetX() {return x;};
        qreal towerGetY() {return y;};
        void deleteTower();
    public slots:
        void towerFire();
    private:
        QTimer *attackTimer;
        qreal attackRange; // Portée d'attaque de la tour en pixels
        QGraphicsEllipseItem *rangeIndicator; // Indicateur de portée d'attaque
        QGraphicsRectItem* towerRect;
        QGraphicsPixmapItem* towerTextureItem;
        int cost;
        int damage;


        qreal height;
        qreal width;


        qreal x;
        qreal y;

};


#endif
