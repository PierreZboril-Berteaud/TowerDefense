//
// Created by pierr on 28/04/2024.
//

#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>

class Tower :public QObject,public QGraphicsRectItem {
    Q_OBJECT
    public:
        QGraphicsPixmapItem *TowerPixmapItem;
        Tower();
        virtual ~Tower();
    private:
        QTimer *timer;
        int tower_damage;
        int cost;
        int range;




};


#endif
