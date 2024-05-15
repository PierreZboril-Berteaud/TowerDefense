#ifndef TOWERDEFENSE_SCORE_H
#define TOWERDEFENSE_SCORE_H

#include <QGraphicsTextItem>
#include <QFont>
class Score :public QGraphicsTextItem{
public :
    Score(QGraphicsItem* parent=nullptr);

    void increase_score();
    int getScore();
private:
    int score;
};


#endif //TOWERDEFENSE_SCORE_H
