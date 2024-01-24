#ifndef TESTMAP_H
#define TESTMAP_H

#include <QtTest>
#include "Map.h"

class TestMap : public QObject
{
    Q_OBJECT

private:
    Map *map;
    QGraphicsScene *scene;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testMapInitialization();
    void testCreateSquare();
    void testEraseSquare();
    void testIsMoveAllowed();
    void testIsSolvable();
};

#endif // TESTMAP_H
