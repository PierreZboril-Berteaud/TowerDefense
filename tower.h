//
// Created by pierr on 28/04/2024.
//

#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>

class Tower :public QObject,public QGraphicsItem {
    Q_OBJECT
    public:
        Tower(QGraphicsItem *parent = nullptr);
        virtual ~Tower();
    private:
        QTimer *timer;
        int tower_damage;
        int cost;
        int range;
    protected:
        // Implement the tower's graphics and collision detection
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget) override;




};


#endif
