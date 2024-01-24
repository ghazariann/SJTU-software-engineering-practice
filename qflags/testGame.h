#ifndef TESTGAME_H
#define TESTGAME_H

#include <QObject>
#include <QtTest>
#include "Game.h"  // Include the header file for the class you're testing

class TestGame : public QObject
{
    Q_OBJECT  // Enables this class to use signals and slots

private:
    Game *game;  // Declare a pointer to the class you're testing

private slots:
    void initTestCase();  // Initialization code, runs before any test functions
    void cleanupTestCase();  // Cleanup code, runs after all test functions
    void testGameTime();  // A test function
    void testAddGameTime();  // Another test function
};

#endif // TESTGAME_H
