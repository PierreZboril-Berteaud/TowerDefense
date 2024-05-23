#include "MyScene.h"
#include <QGraphicsScene>
#include <QApplication>
#include <QPixmap>
#include <QScrollBar>
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

    wave_count =1;
    nbEnemy = 5;
    enemiesSpawned =0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    timer->start(2000);

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
    if (enemiesSpawned < nbEnemy) {
        // Crée un nouvel objet Enemy
        Enemy* enemy = new Enemy();
        enemy->setPos(0, 460);
        addItem(enemy);

        enemiesSpawned++;
    } else {
        timer->stop();
        waveTimer = new QTimer(this);
        waveTimer->setSingleShot(true); //le timer ne s'execute qu'une fois
        connect(waveTimer, &QTimer::timeout, this, &MyScene::startNextWave);
        waveTimer->start(30000);
    }
}

void MyScene::startNextWave() {
    wave_count++;
    nbEnemy *= 2;
    enemiesSpawned = 0;
    timer->start(2000);
}



void MyScene::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Z:
            zoomIn();
            break;
        case Qt::Key_S:
            zoomOut();
            break;
        default:
            QGraphicsScene::keyPressEvent(event);
    }
}


void MyScene::zoomIn() {
    // Augmente le facteur d'échelle
    scaleFactor *= 1.1;
    // Applique le zoom à la vue de la scène
    views().first()->scale(1.1, 1.1);
}

void MyScene::zoomOut() {
    // Diminue le facteur d'échelle
    scaleFactor /= 1.1;
    // Applique le dézoom à la vue de la scène
    views().first()->scale(1 / 1.1, 1 / 1.1);
}

MyScene::~MyScene(){}

