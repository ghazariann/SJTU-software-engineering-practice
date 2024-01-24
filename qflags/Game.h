#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QVector>
#include <QObject>
#include <QGraphicsView>
#include "Player.h"
#include "Map.h"
#include "QFlagScene.h"



class Game : public QObject
{
    Q_OBJECT

public:
    Game(int countdown, int gridLen, int numPlayers);
    ~Game();
    QFlagScene *scene = nullptr;
    QGraphicsView *view = nullptr;
    Map *gameMap = nullptr;
    QVector<Player*> players;
    void addGameTime(int secondsToAdd);
    int getGameTime() const;
    void setGameTime(int newTime);
     int numPlayers;
private:

    QTimer *timer = nullptr;
    QGraphicsTextItem* pauseText = nullptr;

    int countdown = 0;
    int gridLen;

    bool gamePaused = false;
    int gameTime = 0;
    void setupGame();
    QTimer* setupCountdown();
    QGraphicsTextItem* setupPauseText();
    QGraphicsView *setupView();



public slots:
    void togglePauseGame();
    void addTime(int time) {
        addGameTime(time);
    }
};

#endif // GAME_H
