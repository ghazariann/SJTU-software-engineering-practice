#ifndef TESTGRID_H
#define TESTGRID_H

#include <QObject>
#include <QtTest>
#include "Grid.h"

class TestGrid : public QObject
{
    Q_OBJECT

private:
    Grid *grid;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testInitialColor();
    void testSpecialBorder();
    void testSpecialityColor();
};

#endif // TESTGRID_H
