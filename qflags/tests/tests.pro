# Project created by QtCreator
# -------------------------------------------------
# This is the .pro file for the test application.

QT       += core gui widgets testlib  # Include necessary Qt modules

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
SOURCES += \
        ../Game.cpp \
        ../GameMenu.cpp \
        ../Grid.cpp \
        ../Map.cpp \
        ../Player.cpp \
        ../QFlagScene.cpp \
        ../SaveManager.cpp \
    TestRunner.cpp \
    testGame.cpp \
    testGameMenu.cpp \
    testGrid.cpp \
    testMap.cpp \
    testPlayer.cpp \
    testQFlagScene.cpp \
    testSaveManager.cpp


HEADERS += \
    ../Game.h \
    ../GameMenu.h \
    ../Grid.h \
    ../Map.h \
    ../Player.h \
    ../PlayerSignals.h \
    ../QFlagScene.h \
    ../SaveManager.h \
    ../testGame.h \
    testGame.h \
    testGameMenu.h \
    testGrid.h \
    testMap.h \
    testPlayer.h \
    testQFlagScene.h \
    testSaveManager.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Include path to the main project directory
INCLUDEPATH += ../

# Libraries (if any)
# LIBS += -L/path/to/libs -lmylib

# Test configuration
CONFIG += testcase

# Run qmake again if you modify this file.
