//
// Created by pierr on 14/05/2024.
//
#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#ifndef TOWERDEFENSE_GRID_H
#define TOWERDEFENSE_GRID_H


class GridCell : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    GridCell(int x, int y, int size, QGraphicsItem *parent = nullptr) : QObject(), QGraphicsRectItem(x, y, size, size, parent) {
        setPen(QPen(Qt::black)); // Couleur de la bordure
        setBrush(QBrush(Qt::white)); // Couleur de fond
    }
};


#endif //TOWERDEFENSE_GRID_H
