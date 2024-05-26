
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
void Score::increase_score() {
    score++;

    setPlainText(QString("Score: ")+QString::number(score));
}
void Gold::increase_gold(int add_gold){
    set_gold(get_gold()+add_gold);
    setPlainText(QString("Or: ")+QString::number(get_gold()));
}
void Gold::decrease_gold(int cost){
    set_gold(get_gold() - cost);
    setPlainText(QString("Or: ")+QString::number(get_gold()));
}
Score::~Score(){}
Gold::~Gold(){}