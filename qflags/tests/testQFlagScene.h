#ifndef TESTQFLAGSCENE_H
#define TESTQFLAGSCENE_H

#include <QtTest>
#include "QFlagScene.h"
#include "Map.h"

class TestQFlagScene : public QObject
{
    Q_OBJECT

private:
    QFlagScene *scene;
    Map *map;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testSceneInitialization();
    void testKeyPressEvent();
    void testMousePressEvent();
};

#endif // TESTQFLAGSCENE_H
