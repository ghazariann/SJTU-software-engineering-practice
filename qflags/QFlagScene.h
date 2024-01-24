#ifndef QFLAGSCENE_H
#define QFLAGSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsView>

class QFlagScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QFlagScene(int sceneSize,  QObject *parent = nullptr);
       void mousePressEvent(QMouseEvent *event);

signals:
    void pauseGame();
    void saveGame();
    void movePlayer1(int direction);
    void movePlayer2(int direction);
    void mouseClicked(QPoint point);
    void quitGame();


protected:
    void keyPressEvent(QKeyEvent *event) override;
    int sceneSize;

};

#endif // QFLAGSCENE_H
