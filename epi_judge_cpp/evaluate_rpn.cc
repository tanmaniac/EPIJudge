#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;

void insertToStack(std::string value, std::stack<int> &operands, std::stack<char> &operators) {
    if (value == "+" || value == "-" || value == "*" || value == "/") {
        operators.push(value[0]);
    } else {
        operands.push(std::stoi(value));
    }
}

template<typename T>
void evaluateStack(std::stack<int> &operands, std::stack<char> &operators,
                   std::unordered_map<char, std::function<T>> &opMap) {
    if (!operators.empty()) {
        // Pop the first two values off the stack
        int y = operands.top();
        operands.pop();
        int x = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        // Evaluate and push the new value back onto the operand stack
        operands.push(opMap[op](x, y));
    }
}

int Evaluate(const string& expression) {
    std::stack<int> operands;
    std::stack<char> operators;
    std::unordered_map<char, std::function<int(int, int)>> opMap = {
            {'+', [](int x, int y) { return x + y; }},
            {'-', [](int x, int y) { return x - y; }},
            {'/', [](int x, int y) { return x / y; }},
            {'*', [](int x, int y) { return x * y; }}
    };
    std::string delimiters = ",";
    int prev = 0, next = 0;
    while ((next = expression.find_first_of(delimiters, prev)) != std::string::npos) {
        insertToStack(expression.substr(prev, next - prev), operands, operators);
        evaluateStack(operands, operators, opMap);
        prev = next + 1;
    }
    if (prev < expression.size()) {
        insertToStack(expression.substr(prev), operands, operators);
        evaluateStack(operands, operators, opMap);
    }

    return operands.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
