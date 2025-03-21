
#include "score.h"

Score::Score(QGraphicsItem* parent): QGraphicsTextItem(parent){
    score = 0;

    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
    setPos(0, 30);

}
Gold::Gold(QGraphicsItem* parent){
    gold = 100;
    setPlainText(QString("Or: ") + QString::number(gold));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("times",16));
    setPos(0, 60);
}
void Score::increaseScore() {
    score++;

    setPlainText(QString("Score: ")+QString::number(score));
}
void Gold::increaseGold(int addGold){
    setGold(getGold()+addGold);
    setPlainText(QString("Or: ")+QString::number(getGold()));
}
void Gold::decreaseGold(int cost){
    setGold(getGold() - cost);
    setPlainText(QString("Or: ")+QString::number(getGold()));
}
Score::~Score(){}
Gold::~Gold(){}