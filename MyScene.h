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


#include "tower.h"
#include "enemy.h"
#include "health.h"
#include "score.h"

class MyScene : public QGraphicsScene{
    Q_OBJECT

    public:
        MyScene(QObject* parent = nullptr);


        void keyPressEvent(QKeyEvent * event);
        //void deleteEnemy()
        virtual ~MyScene();

        void zoomIn();
        void zoomOut();

        int get_nbEnemy() {return nbEnemy;}
        void set_nbEnemy(int nbEnemy) {this->nbEnemy = nbEnemy;}
        int get_wave() {return wave_count;}
        int set_wave(int wave) {this->wave_count = wave;}
        int getCurrentScore() const;
        void delete_score();

        signals:
            void gameOver();


    private:
        QTimer* timer= nullptr;
        QTimer* waveTimer=nullptr;
        qreal scaleFactor;  // Facteur d'échelle pour le zoom
        int wave_count;
        int nbEnemy;
        int enemiesSpawned;
        Health* health;
        Score* score;
        Gold* gold;


    private slots:
        void spawnEnemy();
        void reachedEnd();
        void startNextWave();
        void increase_score();
    public slots:
        void game_over();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override; //Override set à redefinir une fonction d'une classe mere

        QPixmap* mapPixmap;


};




#endif
