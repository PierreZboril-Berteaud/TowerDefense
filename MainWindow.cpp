#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    layout = new QVBoxLayout;
    centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    playButton = new QPushButton("Play");
    playButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFFFFFFF;"
            "   color: black;"
            "   font-size: 30px;"
            "   border-radius: 10px;"
            "   padding: 20px 60px;"
            "   margin: 15px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #2980b9;"
            "}"
    );
    connect(playButton, &QPushButton::clicked, this, &MainWindow::slotPlayGame);
    layout->addWidget(playButton);

    leaderboardButton = new QPushButton("Leaderboard");
    leaderboardButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFFFFFFF;"
            "   color: black;"
            "   font-size: 30px;"
            "   border-radius: 10px;"
            "   padding: 20px 60px;"
            "   margin: 15px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #d35400;"
            "}"
    );
    connect(leaderboardButton, &QPushButton::clicked, this, &MainWindow::slotShowLeaderboard);
    layout->addWidget(leaderboardButton);


    exitButton = new QPushButton("Exit");
    exitButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFFFFFFF;"
            "   color: black;"
            "   font-size: 30px;"
            "   border-radius: 10px;"
            "   padding: 20px 60px;"
            "   margin: 15px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #c0392b;"
            "}"
    );
    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    layout->addWidget(exitButton);

    layout->setSpacing(30);

    layout->setAlignment(Qt::AlignCenter);

    setFixedSize(1820, 980);
    centralWidget->setStyleSheet(
            "background-image: url('images/menubackground.png');"
            "background-repeat: no-repeat;"
            "background-position: center;"
    );
}

void MainWindow::slotShowMainMenu() {
    qDebug() << "SlotShowMainMenu : start";

    if(!playButton && !leaderboardButton && !exitButton) {

        // Afficher les boutons du menu principal
        QVBoxLayout *layout = new QVBoxLayout;
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        centralWidget->setLayout(layout);

        playButton = new QPushButton("Play");
        playButton->setStyleSheet(
                "QPushButton {"
                "   background-color: #FFFFFFFF;"
                "   color: black;"
                "   font-size: 30px;"
                "   border-radius: 10px;"
                "   padding: 20px 60px;"
                "   margin: 15px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #2980b9;"
                "}"
        );
        connect(playButton, &QPushButton::clicked, this, &MainWindow::slotPlayGame);
        layout->addWidget(playButton);

        leaderboardButton = new QPushButton("Leaderboard");
        leaderboardButton->setStyleSheet(
                "QPushButton {"
                "   background-color: #FFFFFFFF;"
                "   color: black;"
                "   font-size: 30px;"
                "   border-radius: 10px;"
                "   padding: 20px 60px;"
                "   margin: 15px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #d35400;"
                "}"
        );
        connect(leaderboardButton, &QPushButton::clicked, this, &MainWindow::slotShowLeaderboard);
        layout->addWidget(leaderboardButton);


        exitButton = new QPushButton("Exit");
        exitButton->setStyleSheet(
                "QPushButton {"
                "   background-color: #000000;"
                "   color: black;"
                "   font-size: 30px;"
                "   border-radius: 10px;"
                "   padding: 20px 60px;"
                "   margin: 15px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #c0392b;"
                "}"
        );
        connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
        layout->addWidget(exitButton);

        layout->setSpacing(30);

        layout->setAlignment(Qt::AlignCenter);

        setFixedSize(1820, 980);
        centralWidget->setStyleSheet(
                "background-image: url('images/menubackground.png');"
                "background-repeat: no-repeat;"
                "background-position: center;"
        );
    }
}



void MainWindow::slotPlayGame() {
    //demande un pseudo
    bool ok;
    playerName = QInputDialog::getText(this, tr("Entrez un pseudo"), tr("Pseudo:"), QLineEdit::Normal, "", &ok);

    if (!ok || playerName.isEmpty()) {
        QMessageBox::warning(this, tr("pas de nom"), tr("Vous devez entrer un nom."));
        return;
    }
    // Création de la scène du jeu
    this->mainScene = new MyScene;
    connect(mainScene, &MyScene::gameOver, this, &MainWindow::gameOverF);

    // Création de la vue principale
    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);
    this->setCentralWidget(mainView);
    this->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1820, 980);


}


void MainWindow::slotShowLeaderboard() {
    // Tentative de connexion à la base de données PostgreSQL avec libpqxx
    try {
        // Connexion à la base de données PostgreSQL
        pqxx::connection conn("dbname=towerdefensedb user=postgres password=Isen44N hostaddr=127.0.0.1 port=5432");

        if (!conn.is_open()) {
            QMessageBox::warning(this, "Erreur", "La connexion à la base de données a échoué");
            return;
        }

        // Création de la requête SQL pour récupérer les pseudos et scores
        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT username, score FROM Score ORDER BY score DESC LIMIT 10");

        // Création du tableau pour afficher les données
        leaderboardTable = new QTableWidget;
        leaderboardTable->setColumnCount(2);  // Deux colonnes : Pseudo et Score
        leaderboardTable->setRowCount(res.size());  // Nombre de lignes à afficher en fonction des résultats

        // Appliquer du style pour un affichage plus esthétique
        leaderboardTable->setStyleSheet(
                "QTableWidget {"
                "   background-color: #f5f5f5;"
                "   border: 1px solid #ddd;"
                "   font-size: 14px;"
                "   color: #333;"
                "   gridline-color: #ddd;"
                "}"
                "QTableWidget::item:selected {"
                "   background-color: #70a1d7;"
                "   color: white;"
                "}"
                "QHeaderView::section {"
                "   background-color: #2c3e50;"
                "   color: white;"
                "   font-weight: bold;"
                "   padding: 5px;"
                "}"
                "QTableWidget::item {"
                "   padding: 8px;"
                "}"
                "QTableWidget QTableCornerButton::section {"
                "   background-color: #2c3e50;"
                "}"
        );

        // Parcourir les résultats de la requête et les afficher dans le tableau
        int row = 0;
        for (const auto& row_result : res) {
            QString pseudo = QString::fromStdString(row_result[0].c_str());  // Récupère le pseudo
            QString score = QString::fromStdString(row_result[1].c_str());   // Récupère le score

            leaderboardTable->insertRow(row);
            leaderboardTable->setItem(row, 0, new QTableWidgetItem(pseudo));  // Colonne 0 : Pseudo
            leaderboardTable->setItem(row, 1, new QTableWidgetItem(score));   // Colonne 1 : Score
            ++row;
        }

        // Fermer la connexion
        txn.commit();
        conn.disconnect();

        // Configuration du tableau
        leaderboardTable->setHorizontalHeaderLabels(QStringList() << "Pseudo" << "Score");
        leaderboardTable->resizeColumnsToContents();
        leaderboardTable->setWindowTitle("Leaderboard");
        leaderboardTable->setColumnWidth(0, 200);
        leaderboardTable->setColumnWidth(1, 100);


        leaderboardTable->resize(400, 300);
        leaderboardTable->setFixedSize(400, 300);
        leaderboardTable->show();

    } catch (const std::exception& e) {

        QMessageBox::warning(this, "Erreur", "Une erreur s'est produite lors de l'accès à la base de données : " + QString(e.what()));
    }
}

void MainWindow::gameOverF() {
    if (mainScene) {


        int currentScore = mainScene->getCurrentScore();



        pqxx::connection conn("dbname=towerdefensedb user=postgres password=Isen44N hostaddr=127.0.0.1 port=5432");
        if (conn.is_open()) {
            std::cout << "Connexion réussie à la base de données : " << conn.dbname() << std::endl;
        } else {
            std::cerr << "Connexion échouée !" << std::endl;
        }
        pqxx::work txn(conn);
        txn.exec_params("INSERT INTO Score (username, score) VALUES ($1, $2)", playerName.toStdString(), currentScore);

        txn.commit();

        std::cout << "Données insérées avec succès !" << std::endl;

        conn.disconnect();


    }
    deleteAll();
    slotShowMainMenu();




}
void MainWindow::deleteAll(){
    if(mainScene){
        mainScene = nullptr;
        delete mainScene;
        qDebug() <<"Delete mainScene : ok!";
    }

    if(playButton){
        playButton = nullptr;
        delete playButton;
        qDebug() <<"Delete playbutton : ok!";
    }
    if(leaderboardButton){
        leaderboardButton = nullptr;
        delete leaderboardButton;
        qDebug() <<"Delete leaderboardbutton : ok!";
    }
    if(exitButton){
        exitButton = nullptr;
        delete exitButton;
        qDebug() <<"Delete exitButton : ok!";
    }
    if(leaderboardTable){
        leaderboardTable = nullptr;
        delete leaderboardTable;
        qDebug() <<"Delete leaderboardTable : ok!";
    }
    if(mainView){
        mainView->setScene(nullptr);
        mainView = nullptr;
        delete mainView;
        qDebug() <<"Delete mainView : ok!";

    }

    if(layout){
        layout = nullptr;
        delete layout;
        qDebug() <<"Delete layout : ok!";
    }
    if(centralWidget){
        centralWidget = nullptr;
        delete centralWidget;
        qDebug() <<"Delete centralWidget : ok!";
    }
    qDebug() <<"All delete: ok!";
}
void MainWindow::slotExitGame() {}
MainWindow::~MainWindow() {}