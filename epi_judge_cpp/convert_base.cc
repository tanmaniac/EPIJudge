#include <string>
#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
    if (num_as_string.empty()) return "";
    // Convert to base 10 first
    int sign = (num_as_string[0] == '-') ? -1 : 1;
    int idx = (num_as_string[0] == '-') ? 1 : 0;
    long base10 = 0;
    int pow = num_as_string.size() - 1 - idx;
    for (; idx < num_as_string.size(); idx++, pow--) {
        int value = (num_as_string[idx] <= '9') ? num_as_string[idx] - '0' : num_as_string[idx] - 'A' + 10;
        base10 += value * std::pow(b1, pow);
    }

    // Convert to target base
    std::stringstream converted;
    if (base10 == 0) {
        converted << "0";
    } else {
        while (base10 != 0) {
            int value = base10 % b2;
            char charVal = (value < 10) ? value + '0' : (value % 10 + 'A');
            converted << charVal;
            base10 /= b2;
        }
    }

    if (sign == -1) {
        converted << "-";
    }

    std::string result = converted.str();
    std::reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
