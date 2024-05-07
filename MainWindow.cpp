#include "MainWindow.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QApplication>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{



    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    playButton = new QPushButton("Play");
    connect(playButton, &QPushButton::clicked, this, &MainWindow::slot_playGame);
    layout->addWidget(playButton);

    leaderboardButton = new QPushButton("Leaderboard");
    connect(leaderboardButton, &QPushButton::clicked, this, &MainWindow::slot_showLeaderboard);
    layout->addWidget(leaderboardButton);

    exitButton = new QPushButton("Exit");
    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    layout->addWidget(exitButton);

    mainView = new QGraphicsView;
    setFixedSize(1280, 800);


}

MainWindow::~MainWindow(){}


void MainWindow::slot_playGame() {
    qDebug() << "ça marche";
    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);

    this->setCentralWidget(mainView);
}

void MainWindow::slot_showLeaderboard() {
    qDebug() << "ça marche";
}
void MainWindow::slot_exitGame() {
    qDebug() << "ça marche";
}