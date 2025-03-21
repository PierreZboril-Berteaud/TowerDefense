#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include <QKeyEvent>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QApplication>
#include <QPixmap>
#include <QScrollBar>
#include <cstdlib>
#include <QMenu>
#include <QAction>

#include "tower.h"
#include "enemy.h"
#include "health.h"
#include "score.h"

class MyScene : public QGraphicsScene{
    Q_OBJECT




    private:
        QTimer* timer= nullptr;
        QTimer* waveTimer=nullptr;
        Health* health= nullptr;
        Score* score=nullptr;
        Gold* gold=nullptr;


        std::vector<Tower*> towerList;
        std::vector<Enemy*> enemyList;
        qreal scale_factor;  // Facteur d'échelle pour le zoom
        int waveCount;
        int nbEnemy;
        int enemiesSpawned;
        int goldAdded = 10;

    private slots:
        void spawnEnemy();
        void reachedEnd(int damage);
        void startNextWave();
        void increaseScore();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override; //Override set à redefinir une fonction d'une classe mere

        QPixmap* mapPixmap;

    public slots:
        void gameOverF();

    public:
        MyScene(QObject* parent = nullptr);

        void deleteTowers();
        void deleteEnemy();

        void keyPressEvent(QKeyEvent * event);

        virtual ~MyScene();

        void zoomIn();
        void zoomOut();

        int getNbEnemy() {return nbEnemy;}
        void setNbEnemy(int nbEnemy) {this->nbEnemy = nbEnemy;}
        int getWave() {return waveCount;}
        void setWave(int wave) {this->waveCount = wave;}
        int getCurrentScore() const;

        void addGold();


    signals:
        void gameOver();


};




#endif
