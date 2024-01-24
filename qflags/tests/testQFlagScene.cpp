#include "TestQFlagScene.h"
#include <QKeyEvent>
#include <QMouseEvent>

void TestQFlagScene::initTestCase()
{
    scene = new QFlagScene(500);
    map = new Map(scene, 10, 10);
}

void TestQFlagScene::cleanupTestCase()
{
    delete map;
    delete scene;
}

void TestQFlagScene::testSceneInitialization()
{
    QCOMPARE(scene->sceneRect(), QRectF(0, 0, 500, 500));
}

void TestQFlagScene::testKeyPressEvent()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_P, Qt::NoModifier);
    QCoreApplication::sendEvent(scene, &event);
}

void TestQFlagScene::testMousePressEvent()
{
    QMouseEvent event(QEvent::MouseButtonPress, QPointF(100, 100), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QCoreApplication::sendEvent(scene, &event);
}

