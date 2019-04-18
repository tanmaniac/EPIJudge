#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsPalindrome(const string& s) {
  int left = 0, right = s.size() - 1;
  while (left < right) {
      // Find first character
      while (!std::isalnum(s[left])) {
          left++;
      }

      while (!std::isalnum(s[right])) {
          right--;
      }

      if (std::tolower(s[left]) != std::tolower(s[right])) {
          return false;
      }
      left++;
      right--;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
