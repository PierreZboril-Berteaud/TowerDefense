
#include "score.h"

Score::Score(QGraphicsItem* parent): QGraphicsTextItem(parent){
    score = 0;

    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
    setPos(0, 30);

    /*setPlainText(QString("Gold: ") + QString::number(gold));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("times",16));
    setPos(0, 60);*/
}
Gold::Gold(QGraphicsItem* parent){
    gold = 100;
    setPlainText(QString("Gold: ") + QString::number(gold));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("times",16));
    setPos(0, 60);
}
void Score::increase_score() {
    score++;

    setPlainText(QString("Score: ")+QString::number(score));
}
int Score::getScore() {
    return score;
}
Score::~Score(){}
Gold::~Gold(){}