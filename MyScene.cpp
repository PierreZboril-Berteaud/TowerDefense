#include "MyScene.h"

MyScene::MyScene(QObject* parent) :QGraphicsScene(parent) {
    qDebug() << "Constructeur appelé";

    QPixmap map("./images/1280.jng");
    this->setSceneRect(0,0,map.width() * 0.7,map.height() * 0.7);

    // Création de l'objet Score et ajout à la scène principale
    Score* score = new Score();
    addItem(score);
    // Création de l'objet Health et ajout à la scène principale
    Health* health = new Health();
    health->setPos(health->x()+750,health->y()+500);
    addItem(health);

    // Création et démarrage du timer pour générer les ennemis
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    timer->start(10000);

}
/*void MyScene::keyPressEvent(QKeyEvent * event){
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
}*/

MyScene::~MyScene() {}


void MyScene::spawnEnemy() {
    if (nbEnemy > 0) { // Vérifie s'il reste encore des ennemis à faire apparaître
        Enemy *enemy = new Enemy(); // Crée un nouvel ennemi
        addItem(enemy); // Ajoute l'ennemi à la scène
        nbEnemy--; // Décrémente le nombre d'ennemis restants

    } else {
        timer->stop(); // Arrête le timer lorsque tous les ennemis ont été ajoutés
    }

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