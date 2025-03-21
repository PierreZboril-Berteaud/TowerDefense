

#ifndef TOWERDEFENSE_HEALTH_H
#define TOWERDEFENSE_HEALTH_H

#include <QGraphicsTextItem>
#include <QFont>
class Health:public QGraphicsTextItem {
    Q_OBJECT
public:
    Health(QGraphicsItem* parent=nullptr);
    ~Health();
    void decreasePv(int damage);
    int getHealth() {return health;}
    void setHealth(int pv);
signals:
    void gameOver();
private:
    int health;


};


#endif //TOWERDEFENSE_HEALTH_H
