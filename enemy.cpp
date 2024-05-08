#include "enemy.h"
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>
Enemy::Enemy() {
    setRect(0, 0, 50, 50);
    QString path = QDir::currentPath();
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QPixmap enemyPixmap(path + "/images/1.png");
    enemyPixmapItem = new QGraphicsPixmapItem(enemyPixmap, this);
    enemyPixmapItem->setPos(0, 0);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(150);

}

Enemy::~Enemy() {
    delete move_timer;
}

void Enemy::move() {
    setPos(x() + 10, y());
    if (x() == 200) {
        setPos(x(), y() + 15);
    }
    if (x() > 800) {
        remove_enemy();
    }
}

void Enemy::remove_enemy() {
    move_timer->stop();
    scene()->removeItem(this);
    delete this;
}
