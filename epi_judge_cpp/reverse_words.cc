#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {
  auto& str = *s;
  // First pass: reverse the characters in each word
  int start = 0, finish = 0;
  while (start < str.size()) {
      // Find the next non alphanumeric
      while (std::isalnum(str[finish])) {
          finish++;
      }

      std::reverse(str.begin() + start, str.begin() + finish);
      finish++;
      start = finish;
  }

  // Now just reverse the whole sentence
  std::reverse(str.begin(), str.end());
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
