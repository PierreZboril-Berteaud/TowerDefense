#include "MyScene.h"
#include <QGraphicsScene>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
MyScene::MyScene(QObject* parent) :QGraphicsScene(parent) {
    qDebug() << "Constructeur appelé";
    setSceneRect(0,0,1820,980);
    mapPixmap = new QPixmap("images/mapFinale.png");
    QGraphicsPixmapItem* pixmapItem = addPixmap(*mapPixmap);
    // Définit la position de la pixmap sur la scène
    pixmapItem->setPos(0, 0);


    // Création de l'objet Score et ajout à la scène principale
    Score* score = new Score();
    addItem(score);
    // Création de l'objet Health et ajout à la scène principale
    Health* health = new Health();
    addItem(health);

}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QPointF towerPos = event->scenePos() - QPointF(35, 45); //Centre l'image par rapport au curseur de la souris

        //Fais spawn une tour
        Tower *tower = new Tower();
        tower->setPos(towerPos);
        addItem(tower);
    }
}
MyScene::~MyScene(){}