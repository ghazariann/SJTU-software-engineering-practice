#ifndef TESTGAMEMENU_H
#define TESTGAMEMENU_H

#include <QObject>
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
//    void testPopulate();
    void testOnSinglePlayerClicked();
    void testOnDoublePlayerClicked();
    void testOnContinueClicked();
    void testOnQuitClicked();
};

#endif // TESTGAMEMENU_H
