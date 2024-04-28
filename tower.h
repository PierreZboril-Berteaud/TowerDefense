//
// Created by pierr on 28/04/2024.
//

#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

class Tower : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
        Tower(QGraphicsItem *parent = nullptr);
        virtual ~Tower();
    private:
        QTimer *timer;
        int tower_damage;



};


#endif
