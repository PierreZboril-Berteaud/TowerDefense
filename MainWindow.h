#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

#include "MyScene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene;
    QGraphicsView* mainView;
    QPushButton* playButton;
    QPushButton* leaderboardButton;
    QPushButton* exitButton;



public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void slot_playGame();
    void slot_showLeaderboard();
    void slot_exitGame();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
