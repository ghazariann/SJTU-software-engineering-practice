#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BasicInterpreter.h"
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: // Add these lines
    void onCleanClicked();
    void onRunClicked();
    void displayError(const QString& errorMsg);
    void onInput();
    void onLoadButtonClicked();
    // void onInputRequested(const std::string& varName);
    // void onInputConfirmed();
private:
    Ui::MainWindow *ui;
    BasicInterpreter basicInterpreter;
    std::string varName;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

};
#endif // MAINWINDOW_H
