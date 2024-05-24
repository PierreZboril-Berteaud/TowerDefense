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
#include <QInputDialog>


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
    //demande un pseudo
    bool ok;
    playerName = QInputDialog::getText(this, tr("Entrez un pseudo"), tr("Pseudo:"), QLineEdit::Normal, "", &ok);

    if (!ok || playerName.isEmpty()) {
        QMessageBox::warning(this, tr("pas de nom"), tr("Vous devez entrer un nom."));
        return;
    }
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
    leaderboardTable->setColumnCount(2); // Une seule colonne : score

    std::ifstream file("../Leaderboard.txt");
    if (!file.is_open()) {
        QMessageBox::warning(this, "Erreur", "l'ouverture du fichier à échoué"); // Affiche une erreur si le fichier est introuvable ou s'il n'est pas ouvert
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        std::string pseudo, score;
        std::istringstream iss(line);
        if (std::getline(iss, pseudo, ',') && std::getline(iss, score)) {
            leaderboardTable->insertRow(row);
            leaderboardTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(pseudo))); // Utilisez la colonne 0 pour les pseudo
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
void MainWindow::game_over() {
    if (mainScene) {
        qDebug() << "mainScene is valid";


        int currentScore = mainScene->getCurrentScore();

        qDebug() << "Current Score:";


        std::ofstream file("../Leaderboard.txt", std::ios::app); //Ouvre le fichier en mode lecture
        if (file.is_open()) {
            qDebug() << "Fichier ouvert";
            file << playerName.toStdString() << "," << currentScore<<"\n";
            file.close();

        } else {
            qDebug() << "Ouverture du fichier échoué";
        }
    } else {
        qDebug() << "pas de mainscene";  // Debugging output
    }
    slot_showMainMenu();
}

void MainWindow::slot_exitGame() {}
