#ifndef TESTSAVEMANAGER_H
#define TESTSAVEMANAGER_H

#include <QtTest>
#include "SaveManager.h"
#include "Game.h"

class TestSaveManager : public QObject
{
    Q_OBJECT

private:
    SaveManager *saveManager;
    Game *game;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testSaveGameState();
    void testLoadGameState();
    void testCheckSavedFileExists();
    void testDeleteSavedFile();
};

#endif // TESTSAVEMANAGER_H
