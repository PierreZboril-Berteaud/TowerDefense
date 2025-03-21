#include "MyScene.h"

MyScene::MyScene(QObject* parent) :QGraphicsScene(parent) {
    setSceneRect(0,0,1820,980);
    mapPixmap = new QPixmap("images/map_finale_texture.png");
    QGraphicsPixmapItem* pixmapItem = addPixmap(*mapPixmap);

    pixmapItem->setPos(0, 0);


    score = new Score();
    addItem(score);

    health = new Health();
    addItem(health);

    gold = new Gold();
    addItem(gold);

    waveCount =1;
    nbEnemy = 5;
    enemiesSpawned =0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    timer->start(1000);

    connect(health, &Health::gameOver, this, &MyScene::gameOverF);

}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QPointF towerPos = event->scenePos();
        towerPos.setX(towerPos.x() - 10); // Centre l'image par rapport au curseur de la souris
        towerPos.setY(towerPos.y() - 60);


        QMenu menu;

        // Ajouter des actions pour chaque type de tour
        QAction *towerType1 = new QAction("Tour Type 1 (Coût: 25)", &menu);

        menu.addAction(towerType1);

        QAction *selectedAction = menu.exec(event->screenPos());

        int towerCost = 0;
        int towerType = 0;

        if (selectedAction == towerType1) {
            towerCost = 25;
            towerType = 1;
        }

        if (towerCost > 0 && gold->getGold() >= towerCost) {
            Tower *tower = new Tower(towerPos.x(), towerPos.y(), towerType);
            tower->setPos(towerPos);
            if (tower->isValidPlace()) {
                addItem(tower);
                towerList.push_back(tower);
                gold->decreaseGold(towerCost);
            } else {
                delete tower;
            }
        }
    }
}
void MyScene::spawnEnemy() {
    if (enemiesSpawned < nbEnemy) {
        // Crée un nouvel objet Enemy
        Enemy* enemy = new Enemy(2);

        enemyList.push_back(enemy);
        addItem(enemy);
        connect(enemy, &Enemy::reachedEnd, this, &MyScene::reachedEnd);
        connect(enemy, &Enemy::increaseScore, score, &Score::increaseScore);
        connect(enemy, &Enemy::addGold, this, &MyScene::addGold);
        enemiesSpawned++;

} else {
        timer->stop();
        waveTimer = new QTimer(this);
        waveTimer->setSingleShot(true); //le timer ne s'execute qu'une fois
        connect(waveTimer, &QTimer::timeout, this, &MyScene::startNextWave);
        waveTimer->start(10000);
    }
}

void MyScene::startNextWave() {
    waveCount++;
    nbEnemy *= 2;
    enemiesSpawned = 0;
    timer->start(1500);
}
int MyScene::getCurrentScore() const {
    return score->getScore();
}
void MyScene::reachedEnd(int damage) {
    if (health) { // Vérifie si health est un pointeur valide
        health->decreasePv(10); // Diminue la santé de 10
    }
}
void MyScene::increaseScore(){
    if(score){
        score->increaseScore();
    }
}
void MyScene::addGold(){
    if(gold){
        gold->increaseGold(goldAdded);
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
void MyScene::gameOverF(){
    qDebug() << "Game Over";

    if (timer) {
        timer->stop();

        timer = nullptr;
        delete timer;
        qDebug()<<"delete timer: ok!";
    }

    if (waveTimer) {
        waveTimer->stop();

        waveTimer = nullptr;
        delete waveTimer;
        qDebug()<<"delete waveTimer : ok!";
    }
    if(gold){
        removeItem(gold);

        gold = nullptr;
        delete gold;
        qDebug() << "Delete gold : ok!";
    }
    if (mapPixmap) {

        mapPixmap = nullptr;
        delete mapPixmap;
        qDebug()<<"delete pixmap : ok!";
    }
    deleteTowers();
    deleteEnemy();

    qDebug()<<" Tout les deletes: ok!";


    emit gameOver();
}

void MyScene::deleteTowers(){
    if(towerList.size()!=0) {
        for (size_t i = 0; i < towerList.size(); i++) {
            towerList[i]->deleteTower();
            towerList[i] = nullptr;
            delete towerList[i];
        }
    }
}

void MyScene::deleteEnemy(){
    if(enemyList.size() != 0){
        for(size_t i=0; i<enemyList.size(); i++){
            if(enemyList[i]) {
                enemyList[i]->deleteEnemys();
                enemyList[i] = nullptr;
                delete enemyList[i];
            }
        }
    }
}

MyScene::~MyScene(){}

