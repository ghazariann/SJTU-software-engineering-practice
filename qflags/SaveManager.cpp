#include "SaveManager.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QDir>
SaveManager::SaveManager() {
    QDir dir = QDir::current();
       dir.cdUp(); // Go up one directory from the current
       dir.cd("qflags"); // Enter the "qflags" directory

        filepath = dir.absolutePath() + "/gameState.txt";
}
void SaveManager::saveGameState(const Game *game) {

    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing";
        return;
    }

    QTextStream out(&file);

    // Serialize the map
    QString serializedMap = game->gameMap->serialize();

    // Save remaining time
    out << game->getGameTime() << "\n";

    // Save the state of each player
    for (const Player *player : game->players) {
        out << player->x() << " " << player->y() << " " << player->getScore() << "\n";
    }

    // Save the serialized map
    out << serializedMap << "\n";

    file.close();
    qDebug() << "Game is saved";
}

void SaveManager::loadGameState(Game *game) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading";
        return;
    }

    QTextStream in(&file);

    // Load remaining time
    int remainingTime;
    in >> remainingTime;
    game->setGameTime(remainingTime);

    // Load the state of each player
    for (Player *player : game->players) {
        int x, y, score;
        in >> x >> y >> score;
        player->setX(x);
        player->setY(y);
        player->setScore(score);
        player->updateScore();
    }

    // Load the serialized map
    QString serializedMap;
    in.readLine();  // Consume the remaining newline character
    while (!in.atEnd()) {
        QString line = in.readLine();
        serializedMap += line + "\n";
    }

    game->gameMap->deserialize(serializedMap);

    file.close();
    qDebug() << "Game is loaded";
}
bool SaveManager::checkSavedFileExists() {
    QFile file(filepath);
    return file.exists();
}

void SaveManager::deleteSavedFile() {
    QFile file(filepath);
    if (file.exists()) {
        file.remove();
    }
}
