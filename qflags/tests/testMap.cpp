#include "TestMap.h"
#include <QGraphicsScene>

void TestMap::initTestCase()
{
    scene = new QGraphicsScene();
    map = new Map(scene, 10, 10);
}

void TestMap::cleanupTestCase()
{
    delete map;
    delete scene;
}

void TestMap::testMapInitialization()
{
    QCOMPARE(map->getGridLen(), 10);
    QCOMPARE(map->getCellSize(), 10);
}

void TestMap::testCreateSquare()
{
    map->createSquare(0, 0, 1);
    Grid* grid = map->getGridAt(0, 0);
    QVERIFY(grid != nullptr);
    QCOMPARE(grid->colorIndex, 1);
}

void TestMap::testEraseSquare()
{
    map->eraseSquare(0, 0);
    Grid* grid = map->getGridAt(0, 0);
    QVERIFY(grid == nullptr);
}

void TestMap::testIsMoveAllowed()
{
    bool isAllowed = map->isMoveAllowed(5, 5);
    QCOMPARE(isAllowed, false);
}

void TestMap::testIsSolvable()
{
    auto solvable = map->isSolvable();
    QVERIFY(solvable.first.x() != -1 || solvable.second.x() != -1);
}

