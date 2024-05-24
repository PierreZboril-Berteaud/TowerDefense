

#ifndef TOWERDEFENSE_HEALTH_H
#define TOWERDEFENSE_HEALTH_H

#include <QGraphicsTextItem>
#include <QFont>
class Health:public QGraphicsTextItem {
    Q_OBJECT
public:
    Health(QGraphicsItem* parent=nullptr);
    ~Health();
    void decrease_pv();
    int get_health() {return health;}
    void set_health(int pv);
signals:
    void gameOver();
private:
    int health;


};


#endif //TOWERDEFENSE_HEALTH_H
