#include "MyScene.h"
#include "menu.h"

MyScene::MyScene(QObject* parent) :QGraphicsScene(parent) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    timer->start(5000);

}
void MyScene::keyPressEvent(QKeyEvent * event){
    if(event->key() == Qt::Key_Left){
        setPos(x()-100,y());
        qDebug() <<"Left Key pressed";
    }
    else if (event->key() == Qt::Key_Right){
        setPos(x()+10,y());
        qDebug() <<"Right Key pressed";
    }
    else if (event->key() == Qt::Key_Up){
        setPos(x(),y()-10);
        qDebug() <<"Up Key pressed";
    }
    else if (event->key() == Qt::Key_Down){
        setPos(x(),y()+10);
        qDebug() <<"Down Key pressed";
    }
}

MyScene::~MyScene() {
}
void MyScene::spawnEnemy() {
    if (nbEnemy > 0) { // Vérifie s'il reste encore des ennemis à faire apparaître
        Enemy *enemy = new Enemy(); // Crée un nouvel ennemi
        addItem(enemy); // Ajoute l'ennemi à la scène
        nbEnemy--; // Décrémente le nombre d'ennemis restants
    } else {
        timer->stop(); // Arrête le timer lorsque tous les ennemis ont été ajoutés
    }
}
void MyScene::spawnTower(){
    Tower *tower = new Tower();
    tower->setPos(5, 5);
    addItem(tower);
}