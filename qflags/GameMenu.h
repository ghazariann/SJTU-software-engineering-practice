#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSize>
#include <QLineEdit>
#include <QGraphicsView>
class GameMenu : public QWidget
{
    Q_OBJECT

public:
    GameMenu(QSize windowSize);
    void populate(QPushButton *singlePlayerButton, QPushButton *doublePlayerButton, QPushButton *continueButton, QPushButton *quitButton);
    int time;
    int gridSize;

public slots:
    void onSinglePlayerClicked();
    void onDoublePlayerClicked();
    void onContinueClicked();
    void onQuitClicked();

signals:
    void singlePlayerClicked();
    void doublePlayerClicked();
    void continueClicked();
    void quitClicked();
private:
//    bool lastGameExists;
    QGraphicsView * nextView;
    QSize  windowSize;
    QLineEdit *mapWidth;
    QLineEdit *mapHeight;
    QLineEdit *timerValue;
};

#endif // GAMEMENU_H
