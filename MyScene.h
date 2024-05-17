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


        //void keyPressEvent(QKeyEvent * event);
        //void deleteEnemy();
        virtual ~MyScene();

    private:
        QTimer* timer= nullptr;
        void buildMap();
        int nbEnemy=5;

    private slots:

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override; //Override set à redefinir une fonction d'une classe mere
        void spawnEnemy();
        QPixmap* mapPixmap;


};




#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
