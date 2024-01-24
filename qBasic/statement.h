#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "expression.h"
#include <QObject>
#include <QInputDialog>

class Statement {
public:
    virtual ~Statement() {}
    virtual std::string toString(State& state) const  = 0;
    std::string indent = "\n    ";
    virtual void execute(State& state) = 0;
    void setExecutionCount(int count) {
        executionCount = count;
    }
    int getExecutionCount() const {
        return executionCount;
    }
    int executionCount = 0;
};

class LetStmt : public Statement {
public:
    LetStmt(const std::vector<std::string>& tokens)
                : variable(tokens[1]),
        expression(Expression::parseExpression(tokens.begin() + 3, tokens.end())) {} // just for now get one element
    std::string variable;
    Expression* expression;

    std::string toString(State& state) const override{
        // return "LET =" + indent + variable + expression->toString(indent);
        std::string result = "LET = " + std::to_string(executionCount) + indent;
        result += variable + " " + std::to_string(state.getUseCount(variable));
        result += expression->toString(indent);
        return result;
    }
    void execute(State& state) override {
        int value = expression->eval(state);
        state.setVariable(variable, value);
    }
};

class RemStmt : public Statement {
public:
    RemStmt(const std::vector<std::string>& tokens) {
        // Assuming the comment starts from the second token
        comment = std::accumulate(
            tokens.begin() + 1, tokens.end(), std::string(),
            [](const std::string& a, const std::string& b) -> std::string {
                return a + (!a.empty() ? " " : "") + b; //
            });

    }
    std::string comment;
    std::string toString(State& state) const override{
    return "REM " + std::to_string(executionCount) + indent + comment;
    }
    void execute(State& state) override {
    }
};

class IfThenStmt : public Statement {
public:
    IfThenStmt(const std::vector<std::string>& tokens) {
        // Assuming the expression starts from the second token and ends before "THEN"
        auto thenPos = std::find(tokens.begin(), tokens.end(), "THEN");
        condition = Expression::parseExpression(tokens.begin() + 1, thenPos);
        lineNumber = std::stoi(*(thenPos + 1));
    }
    int trueCount = 0;
    int falseCount = 0;
    Expression* condition;
    int lineNumber;

    std::string toString(State& state) const{
    // return "IF THEN" + condition->toString(indent) + indent + std::to_string(lineNumber);
        std::string result = "IF THEN " + std::to_string(trueCount) + " " + std::to_string(falseCount);
        result += condition->toString(indent) + indent + std::to_string(lineNumber);
        return result;
    }
    void execute(State& state) override {
        if (condition->eval(state)) {
            trueCount++;
            state.setProgramCounter(lineNumber);
        }
        else{
            falseCount++;
        }
    }
};

class GotoStmt : public Statement {
public:
    GotoStmt(const std::vector<std::string>& tokens) {
        // Assuming the line number is the second token
        lineNumber = std::stoi(tokens[1]);
    }
    int lineNumber;
    std::string toString(State& state) const override{
        return "GOTO " + std::to_string(executionCount) + indent + std::to_string(lineNumber);
    }
    void execute(State& state) override {
        state.setProgramCounter(lineNumber);
    }
};

class PrintStmt : public Statement {
public:
    PrintStmt(const std::vector<std::string>& tokens) {
        // Assuming the expression starts from the second token
        expression = Expression::parseExpression(tokens.begin() + 1, tokens.end());
    }
    Expression* expression;
    std::string toString(State& state) const override{
    // return "PRINT"+expression->toString(indent);
    return "PRINT " + std::to_string(executionCount) +  expression->toString(indent);
    }
    void execute(State& state) override {
        expression->eval(state);
    }
};

class InputStmt : public Statement {
public:
    InputStmt(const std::vector<std::string>& tokens) {
        // Assuming the variable name is the second token
        variableName = tokens[1];
    }
    std::string variableName;
    std::string toString(State& state) const override{
    // return "INPUT " + variableName;
     return "INPUT " + std::to_string(executionCount) + variableName;
    }
    void execute(State& state) override {
        bool ok;
        int inputValue = QInputDialog::getInt(nullptr, "Input Required",
                                              QString::fromStdString(variableName + ": "),
                                              0, INT_MIN, INT_MAX, 1, &ok);
        if (ok) {
            state.setVariable(variableName, inputValue);
        }
    }
};
