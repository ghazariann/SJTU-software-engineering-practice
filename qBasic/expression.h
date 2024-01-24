#include <vector>
#include <string>
#include <algorithm>
#include "state.h"
#include <cmath>
#include <QMessageBox>
class Expression {
public:
    virtual ~Expression() {}
    virtual std::string toString(const std::string indent = "\n") const = 0;
     static Expression* parseExpression(std::vector<std::string>::const_iterator start,
                                       std::vector<std::string>::const_iterator end);
        virtual int eval( State & state) = 0;
    // ... other methods ...
};

class ConstantExp : public Expression {
public:
    ConstantExp(int value) : value(value) {}
    int value;
    std::string toString(const std::string indent = "\n") const override {
        return indent + std::to_string(value);
    }
    int eval( State& state)  override {
        return value;
    }
};

class IdentifierExp : public Expression {
public:
    IdentifierExp(const std::string& name) : name(name) {}
    std::string name;
    std::string toString(const std::string indent = "\n") const override {
        return indent + name;
    }
    int eval(State& state) override {
        state.incrementUseCount(name);
        if (!state.hasVariable(name)) {
            QMessageBox::critical(nullptr, "Execution Error",
                                  "Variable '" + QString::fromStdString(name) + "' not found.");
            return 0; // Or handle this case as appropriate
        }
        return state.getVariable(name);
    }
};

class CompoundExp : public Expression {
public:
    CompoundExp(const std::string& op, Expression* left, Expression* right)
        : op(op), left(left), right(right) {}
    std::string op;
    Expression *left, *right;
    std::string toString(const std::string indent = "\n") const override {
        std::string new_indent = (op == "+" || op == "/" || op == "-" || op == "*" || op == "**") ? indent+"    ": indent;
        return indent + op  + left->toString(new_indent)  + right->toString(new_indent);
    }

    int eval( State& state)  override {
        int leftVal = left->eval(state);
        int rightVal = right->eval(state);

        if (op == ">") {
            return leftVal > rightVal;
        } else if (op == "<") {
            return leftVal < rightVal;
        } else if (op == "==") {
            return leftVal == rightVal;
        }
        else if (op == "="){
            return leftVal == rightVal;
        }
        else if (op == "+") {
            return leftVal + rightVal;
        } else if (op == "-") {
            return leftVal - rightVal;
        } else if (op == "*") {
            return leftVal * rightVal;
        } else if (op == "/") {
            if (rightVal == 0) {
                        QMessageBox::critical(nullptr, "Error", "Devision by zero");
            }
            return leftVal / rightVal;
        } else if (op == "MOD") {
            if (rightVal == 0) {
                QMessageBox::critical(nullptr, "Error", "Modulo by zero");
            }
            // Implement the modulo operation as per the specific rules
            int result = leftVal % rightVal;
            if ((result < 0 && rightVal > 0) || (result > 0 && rightVal < 0)) {
                result += rightVal;
            }
            return result;
        } else if (op == "**") {
            return std::pow(leftVal, rightVal);  // Exponentiation
        } else {
            QMessageBox::critical(nullptr, "Error", "Unknown operator");
        }
    }
};
