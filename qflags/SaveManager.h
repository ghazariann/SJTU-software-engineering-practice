#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QGraphicsScene>
#include "Game.h"

class SaveManager {
public:
    SaveManager();
    void saveGameState(const Game *game);
    void loadGameState(Game *game);
     bool checkSavedFileExists();
     void deleteSavedFile();
//     void handleSaveKey(Game *game);
     QString filepath;
};

#endif // SAVEMANAGER_H
