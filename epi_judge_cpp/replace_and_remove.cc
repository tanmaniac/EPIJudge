#include <iterator>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
  // Remove all b's while incrementing the count to determine the final length
  int inspect = 0, curIdx = 0;
  int outputLength = 0;
  for (int i = 0; i < size; i++) {
      if (s[i] != 'b') {
          s[curIdx++] = s[i];
      }
      if (s[i] == 'a') {
          outputLength += 2;
      } else if (s[i] != 'b') {
          outputLength += 1;
      }
  }
  // Now work backwards, filling in from the end
  int fillIn = outputLength - 1;
  for (curIdx -= 1; curIdx >= 0; curIdx--) {
      if (s[curIdx] == 'a') {
          s[fillIn--] = 'd';
          s[fillIn--] = 'd';
      } else {
          s[fillIn--] = s[curIdx];
      }
  }
  return outputLength;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
