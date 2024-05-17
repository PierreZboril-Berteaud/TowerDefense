#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <iostream>
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>

class Enemy: public QObject,public QGraphicsRectItem{
    Q_OBJECT
    private:
        int PV;
        bool dead;
        int damage;

        QTimer* move_timer =  new QTimer(this);
    public:

        QGraphicsPixmapItem *enemyPixmapItem;
        Enemy();
        ~Enemy();
        //Getters
        bool is_dead();
        int get_pv();
        int get_damage();
        int get_spawnX();
        int get_spawnY();

        //setters
        void set_dead(bool dead);
        void set_damage(int damage);
        void set_pv(int PV);


        void inflict_damage(int damage);
        void remove_enemy();


    private slots:
        void move();

};


#endif //TOWERDEFENSE_ENEMY_H
