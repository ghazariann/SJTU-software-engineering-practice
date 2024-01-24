#include "GameMenu.h"
#include "SaveManager.h"
#include <QDebug>
#include <QApplication>
#include <QMessageBox>

const int SCENE_SIZE = 800;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
        int numOfPlayers;

        GameMenu gameMenu(QSize(SCENE_SIZE,SCENE_SIZE));
        gameMenu.show();
        QEventLoop loop;


       QObject::connect(&gameMenu, &GameMenu::singlePlayerClicked, [&](){
           numOfPlayers = 1;
           loop.quit();
       });

       QObject::connect(&gameMenu, &GameMenu::doublePlayerClicked, [&](){
           numOfPlayers = 2;
           loop.quit();

       });
       QObject::connect(&gameMenu, &GameMenu::quitClicked, [&](){
           QCoreApplication::quit();
           loop.quit();

       });
       loop.exec();  // This will block until loop.quit() is called


    Game *game = new Game(gameMenu.time, gameMenu.gridSize, numOfPlayers);

    SaveManager saveManager;
    bool fileExists = saveManager.checkSavedFileExists();
    if (fileExists){
        QMessageBox::StandardButton reply;
               reply = QMessageBox::question(nullptr, "Continue", "Do you want to continue the last saved game?",
                                             QMessageBox::Yes | QMessageBox::No);
               if (reply == QMessageBox::Yes) {
                   saveManager.loadGameState(game);
               }
}
  // Connect signals and slots
    QObject::connect(game->scene, &QFlagScene::saveGame, [&]() {
      saveManager.saveGameState(game);
    });
     QObject::connect(game->scene, &QFlagScene::pauseGame, game, &Game::togglePauseGame);
     QObject::connect(game->scene, &QFlagScene::quitGame, []() {
         QCoreApplication::quit();
     });
    gameMenu.hide();
    game->view->show();
    return a.exec();
}
