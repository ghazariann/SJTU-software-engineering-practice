#ifndef PLAYERSIGNALS_H
#define PLAYERSIGNALS_H

#include <QObject>

class PlayerSignals : public QObject {
    Q_OBJECT
public:
    explicit PlayerSignals(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void addTime(int time);
       void enableClickMove();
};

#endif // PLAYERSIGNALS_H
