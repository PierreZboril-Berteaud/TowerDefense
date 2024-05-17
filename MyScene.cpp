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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    timer->start(2000);

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
void MyScene::spawnEnemy() {
    if (nbEnemy > 0) { // Vérifie s'il reste encore des ennemis à faire apparaître
        Enemy *enemy = new Enemy(); // Crée un nouvel ennemi
        enemy->setPos(0,450);
        enemy->setPos(0,0);
        addItem(enemy); // Ajoute l'ennemi à la scène
        nbEnemy--; // Décrémente le nombre d'ennemis restants

    } else {
        timer->stop(); // Arrête le timer lorsque tous les ennemis ont été ajoutés
    }

}
MyScene::~MyScene(){}