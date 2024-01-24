#include <QApplication>
#include <QDebug>
#include <QGraphicsView>
#include "GameMenu.h"
#include "QFlagScene.h"
#include "Map.h"
#include "Player.h"
#include "SaveManager.h"


GameMenu::GameMenu( QSize windowSize)
{
//        this->lastGameExists = lastGameExists;
//        this->nextView = nextView;
       this->resize(windowSize);
        this->windowSize = windowSize;
        QPushButton *singlePlayerButton = new QPushButton("Single Player");
        QPushButton *doublePlayerButton = new QPushButton("Double Player");
        QPushButton *continueButton = new QPushButton("Continue Last Game");
        QPushButton *quitButton = new QPushButton("X");
        populate(singlePlayerButton, doublePlayerButton, continueButton, quitButton);
       connect(singlePlayerButton, &QPushButton::clicked, this, &GameMenu::onSinglePlayerClicked);
       connect(doublePlayerButton, &QPushButton::clicked, this, &GameMenu::onDoublePlayerClicked);
//       connect(continueButton, &QPushButton::clicked, this, &GameMenu::onContinueClicked);
       connect(quitButton, &QPushButton::clicked, this, &GameMenu::onQuitClicked);
}

void GameMenu::populate(QPushButton *singlePlayerButton, QPushButton *doublePlayerButton, QPushButton *continueButton, QPushButton *quitButton)
{
    QLabel *title = new QLabel("Start a New Game");
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(24);
    title->setFont(titleFont);

    QVBoxLayout *mainLayout = new QVBoxLayout;


    QHBoxLayout *titleLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Create widgets for map size and timer
    QLabel *mapSizeLabel = new QLabel("Map Size");
    QFont mapFont = title->font();
    mapFont.setPointSize(8);
    mapSizeLabel->setFont(titleFont);

    QLabel *timerLabel = new QLabel("Timer");
    QFont timerFont = title->font();
    timerFont.setPointSize(8);
    timerLabel->setFont(titleFont);

    mapWidth = new QLineEdit("7");
    mapHeight = new QLineEdit("7");
    timerValue = new QLineEdit("60");

    QHBoxLayout *mapSizeLayout = new QHBoxLayout;
    QHBoxLayout *timerLayout = new QHBoxLayout;

    // sizes
    singlePlayerButton->setMinimumSize(windowSize.width() / 4, windowSize.height() / 12);
    doublePlayerButton->setMinimumSize(windowSize.width() / 4, windowSize.height() / 12);
    quitButton->setMinimumSize(windowSize.width() / 16, windowSize.height() / 16);
    // Make input fields small rectangles
       mapWidth->setMaximumSize(windowSize.width() / 30, windowSize.width() / 30);
       mapHeight->setMaximumSize(windowSize.width() / 30, windowSize.width() / 30);
       timerValue->setMaximumSize(windowSize.width() / 30, windowSize.width() / 30);

    // Styling buttons
    singlePlayerButton->setStyleSheet("font-size: 18px;");
    doublePlayerButton->setStyleSheet("font-size: 18px;");
    quitButton->setStyleSheet("font-size: 9px;");

    // setting layouts
    mapSizeLayout->addStretch(1);
    mapSizeLayout->addWidget(mapWidth);
    mapSizeLayout->addWidget(new QLabel("x"));
    mapSizeLayout->addWidget(mapHeight);
     mapSizeLayout->addStretch(1);
        timerLayout->addStretch(1);
    timerLayout->addWidget(timerValue);
    timerLayout->addWidget(new QLabel("secs"));
        timerLayout->addStretch(1);
    titleLayout->addWidget(title);
    buttonLayout->addStretch();
    buttonLayout->addWidget(singlePlayerButton);
    buttonLayout->addWidget(doublePlayerButton);
    buttonLayout->addStretch();

    mainLayout->addWidget(quitButton, 0, Qt::AlignRight); // Move to the top by adding it first
     mainLayout->addStretch();
     mainLayout->addLayout(titleLayout);
     mainLayout->addSpacing(20);  // Add space after title
     mainLayout->addLayout(buttonLayout);
     mainLayout->addSpacing(20);  // Add space after continue button
     mainLayout->addWidget(mapSizeLabel, 0, Qt::AlignCenter);  // Add map size layout
     mainLayout->addLayout(mapSizeLayout, 0);
     mainLayout->addSpacing(20);  // Add space after continue button
     mainLayout->addWidget(timerLabel, 0, Qt::AlignCenter);  // Add timer layout
     mainLayout->addLayout(timerLayout);
     mainLayout->addStretch();
    setLayout(mainLayout);
}
 void GameMenu::onSinglePlayerClicked()
{
     time = timerValue->text().toInt();
     gridSize = mapWidth->text().toInt();
    emit singlePlayerClicked();
}

void GameMenu::onDoublePlayerClicked()
{
    time = timerValue->text().toInt();
    gridSize = mapWidth->text().toInt();
    emit doublePlayerClicked();
}

void GameMenu::onContinueClicked()
{
    time = timerValue->text().toInt();
    gridSize = mapWidth->text().toInt();
    emit continueClicked();
}
void GameMenu::onQuitClicked()
{

    emit quitClicked();
}
