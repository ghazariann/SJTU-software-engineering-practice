#ifndef BASICINTERPRETER_H
#define BASICINTERPRETER_H

#include <map>
#include <string>
#include <QObject>
#include <vector>
#include <memory>
#include "parser.h"

class BasicInterpreter : public QObject {
    Q_OBJECT // This macro is crucial
public:
    State state;
    BasicInterpreter();
    void insertOrUpdateStatement(const std::string& multiLineInput);
    void deleteStatement(int lineNumber);
    std::string getProgramAsString() const;
    void parseCode();
    void runCode();
    std::string getAST();
    // Additional functionality as needed

    int getNextLine(int currentLine) const;
    std::string getCodeResults() const {
        return results;
    }
    std::map<int, std::string> program;
    std::map<int, std::unique_ptr<Statement>> statements;
    std::string results;

signals:
    void errorOccurred(const QString& errorMsg); // Add this signal

private:
    Parser parser;
        std::map<std::string, int> executionCounts;
};

#endif // BASICINTERPRETER_H
