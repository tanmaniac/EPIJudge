#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
    using iterPair = std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>; // current iterator and end iterator
    auto iterGreater = [](iterPair &lhs, iterPair &rhs) -> bool {
        return *(lhs.first) > *(rhs.first);
    };

    std::priority_queue<iterPair, std::vector<iterPair>, decltype(iterGreater)> minHeap(iterGreater);

    // Put the first thing from each array into the minHeap
    for (const auto &arr : sorted_arrays) {
        if (!arr.empty()) {
            minHeap.push({arr.cbegin(), arr.cend()});
        }
    }

    std::vector<int> result;
    while (!minHeap.empty()) {
        // Get the next thing off the heap
        auto nextSmallest = minHeap.top();
        minHeap.pop();
        result.push_back(*(nextSmallest.first));
        if (std::next(nextSmallest.first) != nextSmallest.second) {
            minHeap.push({std::next(nextSmallest.first), nextSmallest.second});
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
