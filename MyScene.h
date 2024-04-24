#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>

#include "enemy.h"
class MyScene : public QGraphicsScene, public QGraphicsRectItem {
    Q_OBJECT

public:
    MyScene(QObject* parent = nullptr);
    void keyPressEvent(QKeyEvent * event);
    //void drawBackground(QPainter* painter, const QRectF &rect);
    virtual ~MyScene();

private:
    QTimer* timer;

};

class MyView: public QGraphicsView{
protected:
    virtual void resizeEvent (QResizeEvent* event)
    {
        this->fitInView(sceneRect());
    }
};

#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
