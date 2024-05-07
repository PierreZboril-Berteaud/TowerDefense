#include "MainWindow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QGraphicsView>
#include <QTableWidget>
#include <QTextStream>
#include <fstream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{



    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    playButton = new QPushButton("Play");
    connect(playButton, &QPushButton::clicked, this, &MainWindow::slot_playGame); //Lance le jeux
    layout->addWidget(playButton);

    leaderboardButton = new QPushButton("Leaderboard");
    connect(leaderboardButton, &QPushButton::clicked, this, &MainWindow::slot_showLeaderboard); //appelle la fonction pour afficher le leaderboard
    layout->addWidget(leaderboardButton);

    exitButton = new QPushButton("Exit");
    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit); //Boutton qui permet de fermer directement la fenêtre
    layout->addWidget(exitButton);

    mainView = new QGraphicsView;
    setFixedSize(1280, 800);


}

MainWindow::~MainWindow(){}


void MainWindow::slot_playGame() {
    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);

    this->setCentralWidget(mainView);
    this->setFixedSize(1280,800);
}

void MainWindow::slot_showLeaderboard() {
    //Cette fonction crée un tableau avec QTableWidget et qui affiche les informations (pseudo/score depuis un fichier txt)
    leaderboardTable = new QTableWidget;
    leaderboardTable->setColumnCount(2); // Deux colonnes : pseudo et score

    std::ifstream file("../Leaderboard.txt");
    if (!file.is_open()) {
        QMessageBox::warning(this, "Error", "Could not open the leaderboard file."); //Affiche une erreur si le fichier est introuvable ou si il n'est pas ouvert
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        std::string pseudo;
        std::string score;
        std::istringstream iss(line);
        if (std::getline(iss, pseudo, ',') && std::getline(iss, score, ',')) {
            leaderboardTable->insertRow(row);
            leaderboardTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(pseudo)));
            leaderboardTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(score)));
            ++row;
        }
    }

    file.close();

    leaderboardTable->setHorizontalHeaderLabels(QStringList() << "Pseudo" << "Score");
    leaderboardTable->resizeColumnsToContents();
    leaderboardTable->setWindowTitle("Leaderboard");
    leaderboardTable->show();
}
void MainWindow::slot_exitGame() {}