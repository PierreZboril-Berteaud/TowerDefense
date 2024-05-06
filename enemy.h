#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <iostream>

class Enemy: public QObject,public QGraphicsRectItem{
    Q_OBJECT
    private:
        int PV;
        bool dead;
        int damage;
        QTimer* move_timer =  new QTimer(this);
    public:
        Enemy();
        ~Enemy();
        //Getters
        bool is_dead();
        int get_pv();
        int get_damage();

        //setters
        void set_dead(bool dead);
        void set_damage(int damage);
        void set_pv(int PV);

        //
        void inflict_damage(int damage);
        void remove_enemy();


    private slots:
        void move();

};


#endif //TOWERDEFENSE_ENEMY_H
