#include "BasicInterpreter.h"
#include <sstream>
#include <cctype>

BasicInterpreter::BasicInterpreter() {}


void BasicInterpreter::insertOrUpdateStatement(const std::string& multiLineInput) {
    std::istringstream multiLineStream(multiLineInput);
    std::string line;
    while (std::getline(multiLineStream, line)) {
        if (!line.empty()) {
            int lineNumber;
            std::string statement;
            std::istringstream iss(line);
            if (!(iss >> lineNumber)) {
                emit errorOccurred("Error: Line number must be an integer");
                return;
            }
            std::getline(iss >> std::ws, statement);
            if (statement.empty()) {
                deleteStatement(lineNumber);
            } else {
                program[lineNumber] = statement;
            }
        }
    }
}

void BasicInterpreter::deleteStatement(int lineNumber) {
    program.erase(lineNumber);
}


void BasicInterpreter::parseCode() {
    // if (statements != NULL)
    // statements.clear();
    for (const auto& line : program) {
        try {
            std::unique_ptr<Statement> stmt(parser.parseStatement(line.second));
            if (stmt) {
                statements[line.first] = std::move(stmt);
            }
        } catch (const std::runtime_error& e) {
            emit errorOccurred(QString::fromStdString(e.what()));
        }
    }
}
// std::string  BasicInterpreter::getAST() const {
//     std::string ast;
//     for (const auto& pair : statements) {
//         ast += std::to_string(pair.first) + " " + pair.second->toString() + "\n";
//     }
//     return ast;
// }

std::string BasicInterpreter::getProgramAsString() const {
    std::ostringstream oss;
    for (const auto& line : program) {
        oss << line.first << " " << line.second << "\n";
    }
    return oss.str();
}

void BasicInterpreter::runCode() {
    int currentLine = program.begin()->first; // Start at the first line

    while (statements.find(currentLine) != statements.end()) {
        state.setProgramCounter(currentLine);
        Statement* currentStmt = statements[currentLine].get();
        if (LetStmt* letStmt = dynamic_cast<LetStmt*>(currentStmt)) {
            // Create a unique key for LET statements by variable name
            std::string key = "LET:" + letStmt->variable;
            executionCounts[key]++;  // Increment the count for this LET variable
            currentStmt->setExecutionCount(executionCounts[key]);

        } else {
            // For all other statement types
            const std::string statementType = typeid(*currentStmt).name();
            executionCounts[statementType]++; // Increment execution count for this type
            currentStmt->setExecutionCount(executionCounts[statementType]);

        }


        if (PrintStmt* printStmt = dynamic_cast<PrintStmt*>(currentStmt)) {
            results += std::to_string(printStmt->expression->eval(state)) + "\n";
        }
        currentStmt->execute(state);

        if (state.getProgramCounter() != currentLine) {
            // If the program counter was changed by GOTO or IF THEN
            currentLine = state.getProgramCounter();
            if (program.find(currentLine) == program.end()) {
                QMessageBox::critical(nullptr, "Execution Error",
                                      "Line number " + QString::number(currentLine) + " not found in the program.");
                return; // Or handle the error as needed
            }
        } else {
            // Move to the next line
            currentLine = getNextLine(currentLine);
        }
    }
}
int BasicInterpreter::getNextLine(int currentLine) const {
    auto it = program.upper_bound(currentLine);
    if (it != program.end()) {
        return it->first; // Return the next line number
    }
    return -1; // Indicate no more lines to execute
}

std::string insertStatistics(const std::string& originalString, const std::string& statistics) {
    size_t pos = originalString.find('\n');
    if (pos != std::string::npos) {
        return originalString.substr(0, pos) + " " + statistics + originalString.substr(pos);
    } else {
        return originalString + " " + statistics;  // If there's no newline, append at the end.
    }
}
std::string BasicInterpreter::getAST()  {
    std::string ast;
    for (const auto& pair : statements) {
        ast += std::to_string(pair.first) + " " + pair.second->toString(state) + "\n";
    }
    return ast;
}
