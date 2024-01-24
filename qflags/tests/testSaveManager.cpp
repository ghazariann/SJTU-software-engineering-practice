#include "TestSaveManager.h"
#include <QFile>

void TestSaveManager::initTestCase()
{
    saveManager = new SaveManager();
    game = new Game(50, 800, 1);
}

void TestSaveManager::cleanupTestCase()
{
    delete game;
    delete saveManager;
}

void TestSaveManager::testSaveGameState()
{
    saveManager->saveGameState(game);
    QVERIFY(QFile::exists(saveManager->filepath));
}

void TestSaveManager::testLoadGameState()
{
    saveManager->loadGameState(game);
}

void TestSaveManager::testCheckSavedFileExists()
{
    bool exists = saveManager->checkSavedFileExists();
    QCOMPARE(exists, true); // Assuming the file should exist
}

void TestSaveManager::testDeleteSavedFile()
{
    saveManager->deleteSavedFile();
    QVERIFY(!QFile::exists(saveManager->filepath)); // Check if the file is deleted
}

