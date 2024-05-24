#ifndef TOWERDEFENSE_SCORE_H
#define TOWERDEFENSE_SCORE_H

#include <QGraphicsTextItem>
#include <QFont>

class Score :public QGraphicsTextItem{
    Q_OBJECT
public :
    Score(QGraphicsItem* parent=nullptr);
    ~Score();
    void increase_score();
    int getScore() {return score;};


private:
    int score;

};
class Gold :public QGraphicsTextItem{
    Q_OBJECT
public:
    Gold(QGraphicsItem* parent=nullptr);
    ~Gold();
    void increase_gold();
    void decrease_gold(int cost);
    int get_gold(){return gold;};
    void set_gold(int gold) {this->gold = gold;};
private:
    int gold;
};

#endif //TOWERDEFENSE_SCORE_H
