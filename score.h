#ifndef TOWERDEFENSE_SCORE_H
#define TOWERDEFENSE_SCORE_H

#include <QGraphicsTextItem>
#include <QFont>

class Score :public QGraphicsTextItem{
    Q_OBJECT
public :
    Score(QGraphicsItem* parent=nullptr);
    ~Score();
    void increaseScore();

    int getScore() {return score;};


private:
    int score;

};
class Gold :public QGraphicsTextItem{
    Q_OBJECT
public:
    Gold(QGraphicsItem* parent=nullptr);
    ~Gold();
    void increaseGold();

    void decreaseGold(int cost);
    void increaseGold(int addGold);
    int getGold(){return gold;};
    void setGold(int gold) {this->gold = gold;};
private:
    int gold;
};

#endif //TOWERDEFENSE_SCORE_H
