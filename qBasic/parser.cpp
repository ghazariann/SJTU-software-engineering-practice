#include "parser.h"
#include <sstream>

Statement* Parser::parseStatement(const std::string& line) {
    std::vector<std::string> tokens = tokenize(line);

    if (tokens.empty()) {
            QMessageBox::critical(nullptr, "Error", "Empty Token");
    }

    if (tokens[0] == "REM") {
        return new RemStmt(tokens);
    } else if (tokens[0] == "LET") {
        return new LetStmt(tokens);
    } else if (tokens[0] == "PRINT") {
        return new PrintStmt(tokens);
    } else if (tokens[0] == "GOTO") {
        return new GotoStmt(tokens);
    } else if (tokens[0] == "IF") {
        return new IfThenStmt(tokens);
    }
    else if (tokens[0] == "INPUT") {
        return new InputStmt(tokens);
    }
    else if (tokens[0] == "END"){
        return nullptr;
    }
}

std::vector<std::string> Parser::tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;

    for (size_t i = 0; i < line.length(); ++i) {
        if (isspace(line[i])) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (line[i] == '(' || line[i] == ')') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, line[i])); // Push the parenthesis as a separate token
        } else {
            token += line[i];
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}
