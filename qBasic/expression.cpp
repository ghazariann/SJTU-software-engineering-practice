#include "expression.h":
#include <stack>

void combineTopTwoOperands(std::stack<std::string>& operators, std::stack<Expression*>& operands) {
    if (operands.size() < 2 || operators.empty()) {
        QMessageBox::critical(nullptr, "Error", "Insufficient operands or no operators available.");
    }
    auto right = operands.top(); operands.pop();
    auto left = operands.top(); operands.pop();
    std::string op = operators.top(); operators.pop();

    operands.push(new CompoundExp(op, left, right));
}
bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" ||
           token == "MOD" || token == "**" || token == ">" || token == "<" || token == "=";
}
bool isHigherPrecedence(const std::string& op1, const std::string& op2) {
    std::map<std::string, int> precedence = {
        {"**", 4},
        {"*", 3}, {"/", 3}, {"MOD", 3},
        {"+", 2}, {"-", 2},
        {">", 1}, {"<", 1}, {"=", 1} // Assuming "=" is for comparison
    };

    return precedence[op1] > precedence[op2];
}
Expression* Expression::parseExpression(std::vector<std::string>::const_iterator start,
                                        std::vector<std::string>::const_iterator end) {
    std::stack<std::string> operators;
    std::stack<Expression*> operands;

    for (auto it = start; it != end; ++it) {
        const std::string& token = *it;

        if (token[0] == '-' && token.size() > 1 && std::all_of(token.begin() + 1, token.end(), ::isdigit)) {
            // Handling negative numbers like "-1"
            operands.push(new ConstantExp(std::stoi(token)));
        }
        else if (std::isdigit(token[0])) {
            operands.push(new ConstantExp(std::stoi(token)));
        }
        else if (std::isalpha(token[0])) {
            operands.push(new IdentifierExp(token));
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                combineTopTwoOperands(operators, operands); // Function to pop, combine, and push back
            }
            operators.pop(); // Pop the '('
        } else if (isOperator(token)) {
            while (!operators.empty() && isHigherPrecedence(operators.top(), token)) {
                combineTopTwoOperands(operators, operands);
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        combineTopTwoOperands(operators, operands);
    }

    return operands.empty() ? nullptr : operands.top();
}

