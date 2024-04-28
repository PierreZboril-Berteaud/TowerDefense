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
        QTimer* timer;
    public:
        Enemy();
        ~Enemy();

    bool is_dead();
    int get_pv();
    int get_damage();

    void set_damage(int damage);
    void set_pv(int PV);


    public slots:
        void move();

};


#endif //TOWERDEFENSE_ENEMY_H
