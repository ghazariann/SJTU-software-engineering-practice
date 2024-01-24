#include "TestGrid.h"
#include <Qpen>

void TestGrid::initTestCase()
{
    grid = new Grid(0, 0, 1, 0, 10, 0, 0);
}

void TestGrid::cleanupTestCase()
{
    delete grid;
}

void TestGrid::testInitialColor()
{
    QCOMPARE(grid->getColor(), QColor(Qt::green));
}

void TestGrid::testSpecialBorder()
{
    grid->setSpecialBorder();
    QPen pen = grid->pen();
    QCOMPARE(pen.width(), 4);
    QCOMPARE(pen.color(), QColor(Qt::black));
}

void TestGrid::testSpecialityColor()
{
    grid->speciality = 1;
    grid->color();
    QCOMPARE(grid->getColor(), QColor(200, 200, 255));

    grid->speciality = 2;
    grid->color();
    QCOMPARE(grid->getColor(), QColor(200, 255, 200));

    grid->speciality = 3;
    grid->color();
    QCOMPARE(grid->getColor(), QColor(255, 200, 200));
}

