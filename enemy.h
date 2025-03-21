#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <iostream>
#include <QPixmap>
#include <QCoreApplication>

class Enemy: public QObject,public QGraphicsRectItem{
    Q_OBJECT
    private:
        int PV;
        bool dead;
        int damage;
        qreal height;
        qreal width;

        QGraphicsPixmapItem *enemyPixmapItem;
        QTimer* moveTimer =  new QTimer(this);
    signals:
        void reachedEnd(int damage);
        void increaseScore();
        void addGold();
    public:


        Enemy(int enemyType);
        ~Enemy();
        //Getters
        int getPv() {return PV;};
        int getDamage() {return damage;};

        //setters
        void setDead(bool dead) { this->dead = dead;};
        void setDamage(int damage) {this->damage = damage;};
        void setPv(int PV) {this->PV = PV;};


        void inflictDamage(int damage);

        void removeEnemy();
        void deleteEnemys();
        QRectF boundingRect() const;


    private slots:
        void move();


};


#endif //TOWERDEFENSE_ENEMY_H
