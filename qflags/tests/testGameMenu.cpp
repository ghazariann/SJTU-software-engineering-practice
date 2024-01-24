#include <QtTest>
#include "GameMenu.h"

class TestGameMenu : public QObject
{
    Q_OBJECT

private:
    GameMenu *gameMenu;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testPopulate();
    void testOnSinglePlayerClicked();
    void testOnDoublePlayerClicked();
    void testOnContinueClicked();
    void testOnQuitClicked();
};

void TestGameMenu::initTestCase()
{
    QSize windowSize(800, 600);
    gameMenu = new GameMenu(windowSize);
    QVERIFY(gameMenu != nullptr);
}

void TestGameMenu::cleanupTestCase()
{
    delete gameMenu;
    gameMenu = nullptr;
    QVERIFY(gameMenu == nullptr);
}

void TestGameMenu::testOnSinglePlayerClicked()
{
    QSignalSpy spy(gameMenu, SIGNAL(singlePlayerClicked()));
    gameMenu->onSinglePlayerClicked();
    QCOMPARE(spy.count(), 1);
}

void TestGameMenu::testOnDoublePlayerClicked()
{
    QSignalSpy spy(gameMenu, SIGNAL(doublePlayerClicked()));
    gameMenu->onDoublePlayerClicked();
    QCOMPARE(spy.count(), 1);
}

void TestGameMenu::testOnContinueClicked()
{
    QSignalSpy spy(gameMenu, SIGNAL(continueClicked()));
    gameMenu->onContinueClicked();
    QCOMPARE(spy.count(), 1);
}

void TestGameMenu::testOnQuitClicked()
{
    QSignalSpy spy(gameMenu, SIGNAL(quitClicked()));
    gameMenu->onQuitClicked();
    QCOMPARE(spy.count(), 1);
}

