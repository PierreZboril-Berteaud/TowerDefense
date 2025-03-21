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
#include <pqxx/pqxx>
#include <QApplication>
#include <QGraphicsView>
#include <QTextStream>
#include <QInputDialog>


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
    QString playerName;
    QVBoxLayout *layout=nullptr;
    QWidget *centralWidget=nullptr;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
    void deleteAll();

public slots:
    void slotPlayGame();
    void slotShowLeaderboard();
    void slotExitGame();
    void gameOverF();
    void slotShowMainMenu();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
