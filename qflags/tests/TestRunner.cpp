#include <QTest>
#include "TestGame.h"
#include "TestGameMenu.h"
#include "TestGrid.h"
#include "TestPlayer.h"
#include "TestMap.h"
#include "TestQFlagScene.h"
#include "TestSaveManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int status = 0;

    {
        TestGame testGame;
        status |= QTest::qExec(&testGame, argc, argv);
    }

    {
        TestGameMenu testGameMenu;
        status |= QTest::qExec(&testGameMenu, argc, argv);
    }

    {
        TestGrid testGrid;
        status |= QTest::qExec(&testGrid, argc, argv);
    }
    {
        TestPlayer testPlayer;
        status |= QTest::qExec(&testPlayer, argc, argv);
    }
    {
        TestMap testMap;
        status |= QTest::qExec(&testMap, argc, argv);
    }
    {
        TestQFlagScene testQFlagScene;
        status |= QTest::qExec(&testQFlagScene, argc, argv);
    }
    {
        TestSaveManager testSaveManager;
        status |= QTest::qExec(&testSaveManager, argc, argv);
    }
    return status;
}
