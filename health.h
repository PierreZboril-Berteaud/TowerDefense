

#ifndef TOWERDEFENSE_HEALTH_H
#define TOWERDEFENSE_HEALTH_H

#include <QGraphicsTextItem>
#include <QFont>
class Health:public QGraphicsTextItem {
public:
    Health(QGraphicsItem* parent=nullptr);
    ~Health();
    void decrease_pv();
    int get_health();

private:
    int health;

};


#endif //TOWERDEFENSE_HEALTH_H
