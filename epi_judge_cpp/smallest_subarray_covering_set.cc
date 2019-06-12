#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {

    // A map of keywords we have yet to see
    std::unordered_map<string, int> remainingKeywords;
    for (const auto &keyword : keywords) {
        remainingKeywords[keyword]++;
    }

    // Find the first subset, starting at 0, that contains the keywords
    Subarray shortest{-1, -1};
    int numRemaining = keywords.size();
    int left = 0;
    int right = 0;
    for (; right < paragraph.size(); right++) {
        if (keywords.count(paragraph[right]) > 0 && --remainingKeywords.at(paragraph[right]) >= 0) {
            numRemaining--;
        }

        while (numRemaining == 0) {
            // Check if this is the shortest sequence
            if ((shortest.start == -1 && shortest.end == -1) || ((shortest.end - shortest.start) > (right - left))) {
                shortest = {left, right};
            }

            if (keywords.count(paragraph[left]) > 0 && ++remainingKeywords.at(paragraph[left]) > 0) {
                numRemaining++;
            }
            left++;
        }
    }

    return shortest;
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
