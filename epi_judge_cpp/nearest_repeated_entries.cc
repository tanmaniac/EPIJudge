#include <string>
#include <vector>
#include <unordered_map>
#include <limits>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
    std::unordered_map<std::string, int> indexMap;
    int minDistance = std::numeric_limits<int>::max();
    bool matches = false;

    for (int i = 0; i < paragraph.size(); i++) {
        // Check to see if we've already seen this word
        auto search = indexMap.find(paragraph[i]);
        if (search == indexMap.end()) {
            // Haven't seen it so insert
            indexMap.insert({paragraph[i], i});
        } else {
            // We have seen this word, so check if it's closer than the current minimum distance and update index
            minDistance = std::min(minDistance, i - search->second);
            search->second = i;
            matches = true;
        }
    }

    return matches ? minDistance : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
