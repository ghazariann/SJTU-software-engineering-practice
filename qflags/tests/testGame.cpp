#include "Game.h"
#include <QtTest>

class TestGame : public QObject
{
    Q_OBJECT

private:
    Game *game;  // Declare a Game pointer

private slots:
    void initTestCase();  // Initialization
    void cleanupTestCase();  // Cleanup
    void testGameTime();
    void testAddGameTime();
};

void TestGame::initTestCase()
{
    game = new Game(50, 800, 1);

void TestGame::cleanupTestCase()
{
    delete game;
}

void TestGame::testGameTime()
{
    QCOMPARE(game->getGameTime(), 50);
}

void TestGame::testAddGameTime()
{
    game->addGameTime(10);
    QCOMPARE(game->getGameTime(), 60);
}

