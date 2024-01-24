#ifndef TESTGAME_H
#define TESTGAME_H

#include <QObject>
#include <QtTest>
#include "Game.h"

class TestGame : public QObject
{
    Q_OBJECT

private:
    Game *game;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testGameTime();
    void testAddGameTime();
};

#endif // TESTGAME_H
