#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  if (x == 0) return "0";

  bool negative = x < 0;
  long val = std::abs(long(x));
  std::stringstream result;
  while (val != 0){
      result << val % 10;
      val /= 10;
  }
  if (negative) {
      result << "-";
  }
  std::string resultStr = result.str();
  std::reverse(resultStr.begin(), resultStr.end());
  return resultStr;
}

int StringToInt(const string& s) {
  if (s.empty()) return 0;
  int sign = (s[0] == '-') ? -1 : 1;
  int idx = (s[0] == '-') ? 1 : 0;
  int result = 0;
  for (; idx < s.size(); idx++) {
      result *= 10;
      result += s[idx] - '0';
  }

  return result * sign;
}

void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
