#include "MainWindow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QGraphicsView>
#include <QTableWidget>
#include <QTextStream>
#include <QDir>
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

    setFixedSize(1280, 720);
}

MainWindow::~MainWindow() {}

void MainWindow::slot_playGame() {
    // Création de la scène du jeu
    this->mainScene = new MyScene;

    // Création de la vue principale
    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);
    this->setCentralWidget(mainView);
    QString path = QDir::currentPath();
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QString Path_image = path+"/images/1280.jpg";
    QPixmap backgroundImage(Path_image);
    if (!backgroundImage.isNull()) {
        QString styleSheet = "background-image: url(" + Path_image + ");";
        styleSheet += " background-position: center; background-repeat: no-repeat; background-attachment: fixed; background-size: cover;";

        this->centralWidget()->setStyleSheet(styleSheet);

    }
    //si on click sur agrandir la fenetre ça module la taille de l'image
    if(this->centralWidget()->size() != backgroundImage.size()){
        this->centralWidget()->resize(backgroundImage.size());
    }

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

void MainWindow::slot_exitGame() {}
