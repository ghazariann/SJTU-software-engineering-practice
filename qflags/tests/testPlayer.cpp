#include "TestPlayer.h"
#include <QGraphicsScene>
#include "QFlagScene.h"

void TestPlayer::initTestCase()
{
    scene = new QFlagScene(800);
    map = new Map(scene, 10, 10);
    player = new Player(scene, map, 1);
}

void TestPlayer::cleanupTestCase()
{
    delete player;
    delete map;
    delete scene;
}

void TestPlayer::testPlayerInitialization()
{
    QCOMPARE(player->getScore(), 0);
}

void TestPlayer::testMoveAccordingToKey()
{
    player->moveAccordingToKey(Qt::Key_Right);
    QCOMPARE(player->x(), 360);
}

void TestPlayer::testSelectGrid()
{
//    player->selectGrid(5, 5, map);
//    QVERIFY(player->selectedGrid != nullptr);
}

void TestPlayer::testUnselectGrid()
{
    player->unselectGrid();
    QVERIFY(player->selectedGrid == nullptr);
}

void TestPlayer::testScore()
{
    player->setScore(10);
    QCOMPARE(player->getScore(), 10);
}

