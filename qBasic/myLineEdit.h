#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class myLineEdit : public QLineEdit {
    Q_OBJECT

public:
    using QLineEdit::QLineEdit; // Inherit constructors from QLineEdit

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void shiftEnterPressed();
};

#endif // MYLINEEDIT_H
