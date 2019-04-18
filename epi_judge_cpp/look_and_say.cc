#include <string>
#include "test_framework/generic_test.h"
using std::string;

string LookAndSay(int n) {
  std::string result = std::to_string(1);
  for (int i = 1; i < n; i++) {
      // Working front to back
      char curChar = result[0];
      int curCharCount = 1;
      std::stringstream newResult;
      for (int idx = 1; idx < result.size(); idx++) {
          if (result[idx] == curChar) {
              curCharCount++;
          } else {
              newResult << curCharCount << int(curChar - '0');
              curChar = result[idx];
              curCharCount = 1;
          }
      }
      // Grab the last value
      newResult << curCharCount << int(curChar - '0');

      result = newResult.str();
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
