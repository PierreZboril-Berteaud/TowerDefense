#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "MyScene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene=nullptr;
    QGraphicsView* mainView=nullptr;
    QPushButton* playButton=nullptr;
    QPushButton* leaderboardButton=nullptr;
    QPushButton* exitButton=nullptr;
    QTableWidget *leaderboardTable=nullptr;




public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void slot_playGame();
    void slot_showLeaderboard();
    void slot_exitGame();
    void game_over();
    void slot_showMainMenu();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
