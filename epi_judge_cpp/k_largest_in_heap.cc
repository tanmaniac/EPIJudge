#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
    using qPair = std::pair<int, int>;
    auto pairLess = [](const qPair &lhs, const qPair &rhs) {
        return lhs.first < rhs.first;
    };
    std::priority_queue<qPair, std::vector<qPair>, decltype(pairLess)> maxHeap(pairLess);

    maxHeap.push({A[0], 0});

    std::vector<int> kLargest;

    auto leftChild = [](int idx) { return 2 * idx + 1; };
    auto rightChild = [](int idx) { return 2 * idx + 2; };

    for (int i = 0; i < k; i++) {
        auto top = maxHeap.top();
        maxHeap.pop();
        kLargest.push_back(top.first);

        int left = leftChild(top.second);
        int right = rightChild(top.second);
        if (left < A.size()) {
            maxHeap.push({A[left], left});
        }

        if (right < A.size()) {
            maxHeap.push({A[right], right});
        }
    }

  return kLargest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
