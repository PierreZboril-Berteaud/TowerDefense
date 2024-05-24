#include "MainWindow.h"
#include "MyScene.h"
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QGraphicsView>
#include <QTableWidget>
#include <QTextStream>
#include <fstream>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
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

    setFixedSize(1920, 1080);
}
void MainWindow::slot_showMainMenu() {
    // Supprimer toute vue ou scène existante
    if (mainView) {
        mainView->setScene(nullptr);
        delete mainView;
        mainView = nullptr;
    }

    // Afficher les boutons du menu principal
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

    setFixedSize(1920, 1080);
}

MainWindow::~MainWindow() {}

void MainWindow::slot_playGame() {
    // Création de la scène du jeu
    this->mainScene = new MyScene;
    connect(mainScene, &MyScene::gameOver, this, &MainWindow::game_over);

    // Création de la vue principale
    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);
    this->setCentralWidget(mainView);
    this->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920, 1080);


}


void MainWindow::slot_showLeaderboard() {
    // Cette fonction crée un tableau avec QTableWidget et qui affiche les informations (pseudo/score depuis un fichier txt)
    leaderboardTable = new QTableWidget;
    leaderboardTable->setColumnCount(1); // Une seule colonne : score

    std::ifstream file("../Leaderboard.txt");
    if (!file.is_open()) {
        QMessageBox::warning(this, "Error", "Could not open the leaderboard file."); // Affiche une erreur si le fichier est introuvable ou s'il n'est pas ouvert
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        std::string score;
        std::istringstream iss(line);
        if (std::getline(iss, score)) {
            leaderboardTable->insertRow(row);
            leaderboardTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(score))); // Utilisez la colonne 0 pour les scores
            ++row;
        }
    }

    file.close();

    leaderboardTable->setHorizontalHeaderLabels(QStringList() << "Score");
    leaderboardTable->resizeColumnsToContents();
    leaderboardTable->setWindowTitle("Leaderboard");
    leaderboardTable->show();
}
void MainWindow::game_over() {
    if (mainScene) {
        qDebug() << "mainScene is valid"; // Debugging output

        // Attempt to get the current score
        int currentScore = mainScene->getCurrentScore();

        qDebug() << "Current Score:";  // Debugging output

        // Open the file in append mode using std::ofstream
        std::ofstream file("../Leaderboard.txt", std::ios::app);
        if (file.is_open()) {
            qDebug() << "File opened successfully.";  // Debugging output
            file << currentScore << "\n";
            file.close();
            qDebug() << "Score written to file and file closed"; // Debugging output
        } else {
            qDebug() << "Failed to open the file";  // Debugging output
            QMessageBox::warning(this, "Error", "Could not open the leaderboard file to save the score.");
        }
    } else {
        qDebug() << "mainScene is null";  // Debugging output
    }
    slot_showMainMenu();
}

void MainWindow::slot_exitGame() {}
