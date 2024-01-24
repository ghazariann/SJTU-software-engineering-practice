#ifndef STATE_H
#define STATE_H

#endif // STATE_H
#include <string>
#include <map>
#include <functional>
class State {
public:
    // Set the starting line number
    void setProgramCounter(int lineNumber) {
        programCounter = lineNumber;
    }

    // Get the current line number
    int getProgramCounter() const {
        return programCounter;
    }

    // Set a variable's value
    void setVariable(const std::string& name, int value) {
        symbolTable[name] = value;
    }

    // Get a variable's value
    int getVariable(const std::string& name) const {
        return symbolTable.at(name);
    }

    std::function<void(const std::string&)> inputRequestCallback;
    void requestInput(const std::string& varName) {
        if (inputRequestCallback) {
            inputRequestCallback(varName);
        }
    }
    bool hasVariable(const std::string& name) const {
        return symbolTable.find(name) != symbolTable.end();
    }
    void incrementUseCount( std::string& variable) {
        variableUseCount[variable]++;
    }
    int getUseCount(const std::string& variable) const {
        auto it = variableUseCount.find(variable);
        if (it != variableUseCount.end()) {
            return it->second;
        }
        return 0;
    }
private:
    int programCounter = 0;
    std::map<std::string, int> symbolTable;
    std::map<std::string, int> variableUseCount;

};
