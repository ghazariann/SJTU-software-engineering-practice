#include "Game.h"
#include <QMessageBox>
#include <QGraphicsTextItem>
#include <QDebug>

const int CELL_SIZE = 50;
const int SCENE_SIZE = 800;

Game::Game(int countdown, int gridLen, int numPlayers) {
    this->gameTime = countdown;
    this->gridLen =  gridLen;
    this->numPlayers = numPlayers;
    setupGame();
}

Game::~Game() {
//    delete app;
}
QGraphicsView* Game::setupView() {
  QGraphicsView *view = new QGraphicsView(scene);
  view->setFixedSize(SCENE_SIZE, SCENE_SIZE);
  view->setRenderHint(QPainter::Antialiasing);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  return view;
}
void Game::setupGame() {
    scene =  new QFlagScene(SCENE_SIZE);
    view = setupView();
    gameMap = new Map(scene, gridLen, CELL_SIZE);
    timer = setupCountdown();
    QGraphicsTextItem *pauseText = setupPauseText();

    Player *player1 = new Player(scene, gameMap, 1);
    players.append(player1);
    QObject::connect(&players[0]->playerSignals, &PlayerSignals::addTime, this, &Game::addTime);

    Player *player2 = nullptr;
    if (numPlayers == 2) {
        player2 = new Player(scene,gameMap, 2);
        players.append(player2);
    }

    QObject::connect(scene, &QFlagScene::movePlayer1, [=](int key) {
        player1->moveAccordingToKey(key);
    });
    if (player2) {
        QObject::connect(&players[1]->playerSignals, &PlayerSignals::addTime, this, &Game::addTime);
        QObject::connect(scene, &QFlagScene::movePlayer2, [=](int key) {
            player2->moveAccordingToKey(key);
        });
    }

}

QTimer* Game::setupCountdown() {
    QGraphicsTextItem *countdownText = new QGraphicsTextItem();
    countdownText->setPos(10, 10);
    countdownText->setZValue(1);
    countdownText->setDefaultTextColor(Qt::black);
    scene->addItem(countdownText);

    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [=]() mutable {
      int countdownTime = getGameTime();
      countdownText->setPlainText(QString("Time left: %1").arg(countdownTime));
      countdownTime--;
      setGameTime(countdownTime);
      if (countdownTime < 0) {
        timer->stop();
        // Game over logic here
        if (numPlayers == 1) {
          QMessageBox::information(nullptr, "Game Over", "Time's up!");
        } else if (numPlayers == 2) {
          int score1 = players[0]->getScore();
          int score2 = players[1]->getScore();
          QString winnerMessage;
          if (score1 > score2) {
            winnerMessage = "Player 1 wins!";
          } else if (score2 > score1) {
            winnerMessage = "Player 2 wins!";
          } else {
            winnerMessage = "It's a tie!";
          }
          QMessageBox::information(nullptr, "Game Over", winnerMessage);
        }
        QApplication::quit();
      }
    });

    timer->start(1000); // Emit timeout() signal every 1000 ms (1 second)
    return timer;
}

QGraphicsTextItem* Game::setupPauseText() {
    pauseText = new QGraphicsTextItem("Game Paused");
    pauseText->setPos(scene->width() / 2 - 50,
                      scene->height() / 2 - 300); // Adjust these values as needed
    pauseText->setVisible(false);
    scene->addItem(pauseText);
    return pauseText;
}

void Game::togglePauseGame() {
    if (gamePaused) {
      timer->start();
      for (Player *player : players) {
        player->setPaused(false);
      }
      pauseText->setVisible(false);
      gamePaused = false;
    } else {
      timer->stop();
      for (Player *player : players) {
        player->setPaused(true);
      }
      pauseText->setVisible(true);
      gamePaused = true;
    }
}

void Game::addGameTime(int secondsToAdd) {
    gameTime += secondsToAdd;
}

int Game::getGameTime() const {
    return gameTime;
}
void Game::setGameTime(int newTime) {
    gameTime = newTime;
}

