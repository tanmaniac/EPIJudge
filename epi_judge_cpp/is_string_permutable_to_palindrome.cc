#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string& s) {
  std::unordered_map<char, int> charCounts;
  for (const auto& c : s) {
      charCounts[c] += 1;
  }
  // Iterate through the map and count the number of odds
  int numOddCharCounts = 0;
  for (auto iter = charCounts.begin(); iter != charCounts.end(); iter++) {
      if (iter->second % 2 != 0) {
          numOddCharCounts++;
      }
  }

  return numOddCharCounts <= 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
