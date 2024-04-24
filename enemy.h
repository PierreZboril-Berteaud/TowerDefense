#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy: public QObject,public QGraphicsRectItem{
    Q_OBJECT
private:
    int PV;
    bool dead;
public:
    Enemy();
    ~Enemy();
public slots:
    void moove();


};


#endif //TOWERDEFENSE_ENEMY_H
