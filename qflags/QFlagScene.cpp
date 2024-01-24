#include "QFlagScene.h"
#include "Map.h"

QFlagScene::QFlagScene(int sceneSize, QObject *parent) :QGraphicsScene(parent) {
    setSceneRect(0, 0, sceneSize, sceneSize);

}

void QFlagScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_P) {
        emit pauseGame();
    } else if (event->key() == Qt::Key_O) {
        emit saveGame();
    } else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right ||
               event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        emit movePlayer1(event->key());
    } else if (event->key() == Qt::Key_W || event->key() == Qt::Key_A || event->key() == Qt::Key_S || event->key() == Qt::Key_D) {
        emit movePlayer2(event->key());
    }else if (event->key() == Qt::Key_Q) {
        emit quitGame();}
    else {
        QGraphicsScene::keyPressEvent(event);
    }
}



void QFlagScene::mousePressEvent(QMouseEvent *event) {
  emit mouseClicked(event->pos());
}
