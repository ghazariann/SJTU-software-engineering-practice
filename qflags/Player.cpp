#include "Player.h"
#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>


Player::Player( QFlagScene*scene, Map *map, int playerID) : gameMap(map), scene(scene), playerID( playerID )
    {

    setCellSize();
        setPosition();
        initializeScore();
        initializeScoreText();}

    void Player::setCellSize() {
      cellSize = gameMap->getCellSize();
    }

    void Player::setPosition() {
      int sceneSize = gameMap->getSceneSize();
      int mapSize = gameMap->getMapSize();
      setRect(0, 0, cellSize, cellSize);

      int initialX = (sceneSize - mapSize) / 2;
      int initialY = (sceneSize - mapSize) / 2 - 2 * cellSize;

      if (playerID == 1) {
        setPos(initialX, initialY);
      } else if (playerID == 2) {
        setPos(initialX + mapSize - cellSize, initialY);
      }

      scene->addItem(this);
    }

    void Player::initializeScore() {
      score = 0;
      int gridLen = gameMap->getGridLen();
      for (int i = 0; i < gridLen; ++i) {
        colorScoreMap[i] = i + 1;
      }
    }

    void Player::initializeScoreText() {
      scoreText = new QGraphicsTextItem();
      playerLabel = (playerID == 1) ? "Player 1: " : "Player 2: ";
      scoreText->setDefaultTextColor(Qt::black);
      scoreText->setFont(QFont("times", 8));
      scoreText->setPlainText(playerLabel + QString::number(score));

      if (playerID == 1) {
        scoreText->setPos(500, 30);
      } else if (playerID == 2) {
        scoreText->setPos(500, 60);
      }

      scene->addItem(scoreText);
    }

void Player::moveAccordingToKey(int direction) {
  if (isPaused)
    return;

  int newX = x();
  int newY = y();
  int stepSize = gameMap->getCellSize();
  if (playerID == 1){
      if (direction == Qt::Key_Left) {
        newX = x() - stepSize;
      } else if (direction == Qt::Key_Right) {
        newX = x() + stepSize;
      } else if (direction == Qt::Key_Up) {
        newY = y() - stepSize;
      } else if (direction == Qt::Key_Down) {
        newY = y() + stepSize;
      }

  }
   if (playerID == 2){
       if (direction == Qt::Key_A) {
         newX = x() - stepSize;
       } else if (direction == Qt::Key_D) {
         newX = x() + stepSize;
       } else if (direction == Qt::Key_W) {
         newY = y() - stepSize;
       } else if (direction == Qt::Key_S) {
         newY = y() + stepSize;
       }
   }
  // Add your movement logic here, e.g., collision checks
  if (gameMap->isMoveAllowed(newX, newY)) {
    setPos(newX, newY);
  }
  selectGrid(newX, newY, gameMap);
}
void Player::selectGrid(int newX, int newY, Map *gameMap) {
  Grid *touchedGrid = gameMap->getTouchedGrid(newX, newY);
  if (touchedGrid == nullptr)
    return;
  if (touchedGrid->speciality == 1) {
          gameMap->eraseSquare(touchedGrid->x, touchedGrid->y);
             emit playerSignals.addTime(30);
          return;
  }
  else if (touchedGrid->speciality == 2){
       gameMap->eraseSquare(touchedGrid->x, touchedGrid->y);
      gameMap->rearrangeGrids();
      return;
  }
//  else if (touchedGrid->speciality == 3){
//      gameMap->eraseSquare(touchedGrid->x, touchedGrid->y);
//       emit playerSignals.enableClickMove();
//      return;
//  }
  if (selectedGrid != nullptr) { // If there is already a selected grid
    if (selectedGrid == touchedGrid) {
      unselectGrid();
      return;
    }

    // Compare colors of the selected grid and the touched grid
    if (selectedGrid->getColor() == touchedGrid->getColor()) {
      // Delete both grids from the map if their colors are the same
      gameMap->eraseSquare(selectedGrid->x, selectedGrid->y);
      gameMap->eraseSquare(touchedGrid->x, touchedGrid->y);
      selectedGrid = nullptr;
      score+=colorScoreMap[touchedGrid->colorIndex];
      updateScore();  // Update the score

      if (gameMap->checkWinCondition()) {
        QMessageBox::information(nullptr, "Congratulations", "You win!");
        QApplication::quit();
      }

      std::pair<QPoint, QPoint> solvableCheck = gameMap->isSolvable();
      if (solvableCheck.first.x() == -1) {
        QMessageBox::information(nullptr, "Ooo Sorry", "You are stuck");
        QApplication::quit();
      }
    } else {
      // Unselect both grids if their colors are different
      unselectGrid();
      //                        touchedGrid->setOpacity(1.0);
    }
    return;
  }
  touchedGrid->setOpacity(0.5);
  selectedGrid = touchedGrid; // Update the selected grid
}
void Player::unselectGrid() {
  if (selectedGrid != nullptr) {
    selectedGrid->setOpacity(1.0);
    selectedGrid = nullptr;
  }
}
void Player::setPaused(bool value) { isPaused = value; }
void Player::updateScore() {
  scoreText->setPlainText(playerLabel + QString::number(score));
}
void Player::setScore(int score){
    this->score = score;
}
 int Player::getScore() const{
    return this->score;
}
