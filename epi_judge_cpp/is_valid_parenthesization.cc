#include <string>
#include <unordered_map>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
    std::unordered_map<char, char> matchedParens = {
            {'{', '}'},
            {'[', ']'},
            {'(', ')'}
    };
    std::stack<char> parensStack;
    for (const auto &paren : s) {
        if (matchedParens.count(paren)) {
            parensStack.push(paren);
        } else {
            // Check if valid closing parenthesis; else return false
            if (parensStack.empty() || matchedParens.at(parensStack.top()) != paren) {
                return false;
            } else {
                parensStack.pop();
            }
        }
    }

  return parensStack.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
