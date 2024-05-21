#include "MyScene.h"
#include <QGraphicsScene>
#include <QApplication>
#include <QPixmap>
#include <QPen>
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
    timer->start(100);

}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QPointF towerPos = event->scenePos(); //Centre l'image par rapport au curseur de la souris

        //Fais spawn une tour
        Tower *tower = new Tower();
        tower->setPos(towerPos);
        if (tower->is_valid_place()) {
            addItem(tower);
        } else {
            //delete tower; // Supprime la tourelle si la position n'est pas valide
            qDebug() << "Position non valide pour placer la tourelle.";
        }
    }
}
void MyScene::spawnEnemy() {
    while(nbEnemy>0) {
        // Crée un nouvel objet Enemy
        Enemy *enemy = new Enemy();

        // Positionne l'ennemi à l'emplacement initial
        enemy->setPos(0, 460);

        // Ajoute l'ennemi à la scène principale
        addItem(enemy);
        nbEnemy--;
    }

}
MyScene::~MyScene(){}