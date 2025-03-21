cmake_minimum_required(VERSION 3.18)

# Nom du projet
project(TowerDefense LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23) # Utilisation de C++23, modifiez si nécessaire.

# Activer Automoc pour Qt (requis pour la gestion des signaux/slots)
set(CMAKE_AUTOMOC ON)

# Trouver les packages nécessaires (Qt6 et PostgreSQL)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(PostgreSQL REQUIRED)

# Liste des fichiers sources du projet
set(SOURCES
        enemy.cpp
        health.cpp
        MainWindow.cpp
        MyScene.cpp
        projectile.cpp
        score.cpp
        tower.cpp
        )

# Liste des fichiers headers
set(HEADERS
        enemy.h
        health.h
        MainWindow.h
        MyScene.h
        projectile.h
        score.h
        tower.h
        )

# Création de l'exécutable principal
add_executable(TowerDefense main.cpp ${SOURCES} ${HEADERS})

# Lier les bibliothèques nécessaires
target_link_libraries(TowerDefense PRIVATE Qt6::Widgets pq pqxx)

# Inclure les headers de PostgreSQL
target_include_directories(TowerDefense PRIVATE ${PostgreSQL_INCLUDE_DIRS})
