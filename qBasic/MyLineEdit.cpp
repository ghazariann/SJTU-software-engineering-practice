#include "myLineEdit.h"

void myLineEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (event->modifiers() & Qt::ShiftModifier) {
            emit shiftEnterPressed();
        } else {
            QLineEdit::keyPressEvent(event); // Call base class implementation for normal enter
        }
    } else {
        QLineEdit::keyPressEvent(event); // Call base class implementation for other keys
    }
}
