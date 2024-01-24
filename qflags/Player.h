#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "Map.h"
#include "QFlagScene.h"
#include "PlayerSignals.h"
#include <QTimer>
class Player : public QGraphicsRectItem {
public:
  Player(QFlagScene *scene, Map *map, int playerID);

  void moveAccordingToKey(int direction);
  void selectGrid(int newX, int newY, Map *gameMap);
  void unselectGrid();
  void setPaused(bool value);
  void updateScore();
  void setScore(int score);
  int getScore() const;
  PlayerSignals playerSignals;
private slots:

 void disableClickMove();
private:
  QTimer *clickTimer;
     bool canClickMove;
  void initializePlayer();
  void setCellSize();
  void setPosition();
  void initializeScore();
  void initializeScoreText();
  signals:
  void addTime(int time){

  };
  Map *gameMap;
  QFlagScene *scene;
  int playerID;
  int cellSize;
  int score;
  QGraphicsTextItem *scoreText;
  QString playerLabel;
  Grid *selectedGrid = nullptr;
  bool isPaused = false;
  std::map<int, int> colorScoreMap;
};

#endif // PLAYER_H
