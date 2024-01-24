#ifndef TESTPLAYER_H
#define TESTPLAYER_H

#include <QtTest>
#include "Player.h"
#include "QFlagScene.h"
#include "Map.h"

class TestPlayer : public QObject
{
    Q_OBJECT

private:
    Player *player;
    QFlagScene *scene;
    Map *map;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testPlayerInitialization();
    void testMoveAccordingToKey();
    void testSelectGrid();
    void testUnselectGrid();
    void testScore();
};

#endif // TESTPLAYER_H
