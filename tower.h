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
#include <QDebug>

class Tower :public QObject,public QGraphicsRectItem {
    Q_OBJECT
    public:
        QGraphicsPixmapItem *TowerPixmapItem;
        Tower();
        bool is_valid_place();
        virtual ~Tower();
    public slots:
        void tower_fire();
    private:
        QTimer *attack_timer;
        qreal attack_range; // Portée d'attaque de la tour en pixels
        QGraphicsEllipseItem *range_indicator; // Indicateur de portée d'attaque
        int cost;
        int damage;
        qreal height;
        qreal width;

};


#endif
