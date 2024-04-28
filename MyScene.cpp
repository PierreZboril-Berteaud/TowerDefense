#include "MyScene.h"

MyScene::MyScene(QObject* parent) :QGraphicsScene(parent) {
    QGraphicsRectItem* qgri = new QGraphicsRectItem(10, 100, 300, 200); //Crée un rectangle au milieu
    this->addItem(qgri);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30); // Toutes les 30 millisecondes
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
/*
void MyScene::drawBackground(QPainter* painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    QPixmap pixBackground("../images/TestMap.png");
    painter->drawPixmap(QPointF(0,0), pixBackground, sceneRect());
    // pixBackgroud est un attribut de type QPixmap qui contient l’image de fond
}*/
MyScene::~MyScene() {

}
