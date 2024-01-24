#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "statement.h"

class Parser {
public:
    Statement* parseStatement(const std::string& line);
private:
    std::vector<std::string> tokenize(const std::string& line);
};

#endif // PARSER_H
