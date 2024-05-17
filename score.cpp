
#include "score.h"

Score::Score(QGraphicsItem* parent): QGraphicsTextItem(parent){
    score = 0;
    updateScoreText();
    setDefaultTextColor(Qt::blue);
    //setFont(QFont("times",16));
    setPos(0, 30);
}
void Score::increase_score() {
    score++;
    updateScoreText();
}
int Score::getScore(){
    return score;
}
void Score::updateScoreText(){
    setPlainText(QString("Score: ")+ QString::number(score));
}
Score::~Score(){}