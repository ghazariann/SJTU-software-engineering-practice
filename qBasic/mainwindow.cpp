#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "myLineEdit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      basicInterpreter()
{
    ui->setupUi(this);
    connect(ui->btnCleanCode, &QPushButton::clicked, this, &MainWindow::onCleanClicked);
    connect(ui->btnRunCode, &QPushButton::clicked, this, &MainWindow::onRunClicked);
    connect(ui->btnLoadCode, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onInput);
    connect(&basicInterpreter, &BasicInterpreter::errorOccurred, this, &MainWindow::displayError);
    qApp->installEventFilter(this);
    // basicInterpreter.state.inputRequestCallback = [this](const std::string& varName) {
    //     onInputRequested(varName);
    // };
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onInput() {
    QString input = ui->cmdLineEdit->toPlainText();;
    basicInterpreter.insertOrUpdateStatement(input.toStdString());
    ui->CodeDisplay->setText(QString::fromStdString(basicInterpreter.getProgramAsString()));
    ui->cmdLineEdit->clear(); // Clear the input field after processing the input
    basicInterpreter.parseCode();
}
// Slots implementation
void MainWindow::onCleanClicked()
{ ui->ResultDisplay->clear();
    ui->TreeDisplay->clear();
    ui->CodeDisplay->clear();
    ui->cmdLineEdit->clear();
    basicInterpreter.program.clear();
    basicInterpreter.statements.clear();
    basicInterpreter.results.clear();
}

void MainWindow::onRunClicked()
{

    basicInterpreter.runCode();
    ui->ResultDisplay->setText(QString::fromStdString(basicInterpreter.results));
    std::string ast = basicInterpreter.getAST(); // getAST should return a std::string
    ui->TreeDisplay->setText(QString::fromStdString(ast));
}

void MainWindow::displayError(const QString& errorMsg) {
    QMessageBox::critical(this, "Error", errorMsg);
}


bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if ((keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) &&
            (keyEvent->modifiers() & Qt::ShiftModifier)) {
            // Handle Shift+Enter keypress
            onInput(); // Call the method to handle input
            return true; // Indicate that the event was handled
        }
    }
    return QMainWindow::eventFilter(obj, event); // Call base class event filter
}
void MainWindow::onLoadButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open BASIC  File"), "", tr("Text Files (*.bas)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString fileContent = in.readAll();

            file.close();

            // Optionally, process the loaded file to update the BasicInterpreter
            basicInterpreter.insertOrUpdateStatement(fileContent.toStdString());
            std::string code = basicInterpreter.getProgramAsString();
            ui->CodeDisplay->setPlainText(QString::fromStdString(code));
            basicInterpreter.parseCode(); // parses
        }
    }
}
// Slot implementation in MainWindow
// void MainWindow::onInputRequested(const std::string& varName) {
//     this->varName = varName; // Store the variable name
//     ui->cmdLineEdit->setPlainText(QString::fromStdString(varName) + " ? ");
//     connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onInputConfirmed);
// }
// // Slot to handle input confirmation
// void MainWindow::onInputConfirmed() {
//     QString inputText = ui->cmdLineEdit->toPlainText();
//     // Remove the prompt part ("varName ? ") from the inputText before processing
//     int value = inputText.section(' ', 1, -1).toInt();
//     basicInterpreter.state.setVariable(varName, value);
//     ui->cmdLineEdit->clear();
// }



