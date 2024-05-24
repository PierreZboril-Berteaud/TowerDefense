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

    pixmapItem->setPos(0, 0);



    score = new Score();
    addItem(score);

    health = new Health();
    addItem(health);

    gold = new Gold();
    addItem(gold);

    wave_count =1;
    nbEnemy = 5;
    enemiesSpawned =0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    timer->start(1000);

    connect(health, &Health::gameOver, this, &MyScene::game_over);

}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QPointF towerPos = event->scenePos();
        towerPos.setX(towerPos.x() - 10);//Centre l'image par rapport au curseur de la souris
        towerPos.setY(towerPos.y() - 60);
        //Fais spawn une tour
        Tower *tower = new Tower();
        if (gold->get_gold() >= tower->get_cost()) {
            tower->setPos(towerPos);
            if (tower->is_valid_place()) {
                addItem(tower);
                gold->decrease_gold(tower->get_cost());

                qDebug()<<"Il vous reste:"<<gold->get_gold()<<"Gold";
            }
        } else {
            qDebug() << "Pas assez d'argent";
        }
    }
}
void MyScene::spawnEnemy() {
    if (enemiesSpawned < nbEnemy) {
        // Crée un nouvel objet Enemy
        Enemy* enemy = new Enemy();
        enemy->setPos(0, 460);
        addItem(enemy);
        connect(enemy, &Enemy::reachedEnd, this, &MyScene::reachedEnd);
        connect(enemy, &Enemy::increase_score, score, &Score::increase_score);
        connect(enemy, &Enemy::add_gold, this, &MyScene::add_gold);
        enemiesSpawned++;
        qDebug()<<enemy->pos();
    } else {
        timer->stop();
        waveTimer = new QTimer(this);
        waveTimer->setSingleShot(true); //le timer ne s'execute qu'une fois
        connect(waveTimer, &QTimer::timeout, this, &MyScene::startNextWave);
        waveTimer->start(10000);
    }
}

void MyScene::startNextWave() {
    wave_count++;
    nbEnemy *= 2;
    enemiesSpawned = 0;
    timer->start(1500);
}
int MyScene::getCurrentScore() const {
    return score->getScore();
}
void MyScene::reachedEnd() {
    if (health) { // Vérifie si health est un pointeur valide
        health->decrease_pv(); // Diminue la santé de 10
    }
}
void MyScene::increase_score(){
    if(score){
        score->increase_score();
    }
}
void MyScene::add_gold(){
    if(gold){
        gold->increase_gold(gold_added);
    }
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
    scale_factor *= 1.1;
    views().first()->scale(1.1, 1.1);
}

void MyScene::zoomOut() {
    scale_factor /= 1.1;
    views().first()->scale(1 / 1.1, 1 / 1.1);
}
void MyScene::game_over(){
    qDebug() << "Game Over";

    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
        qDebug()<<"test time: ok!";
    }

    if (waveTimer) {
        waveTimer->stop();
        delete waveTimer;
        waveTimer = nullptr;
        qDebug()<<"test wavetimer: ok!";
    }
    if(gold){
        removeItem(gold);
        delete gold;
        gold = nullptr;
    }



    if (mapPixmap) {
        delete mapPixmap;
        mapPixmap = nullptr;
        qDebug()<<"Test pixmap : ok!";
    }

    qDebug()<<"test clear: ok!";


    emit gameOver();
}

MyScene::~MyScene(){}

