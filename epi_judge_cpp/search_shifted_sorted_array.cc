#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
    int lo = 0;
    int hi = A.size() - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] < A[hi]) {
            // Must reside in the left half, so go left
            hi = mid;
        } else {
            // Must reside in the right half since mid > hi
            lo = mid + 1;
        }
    }
    return lo;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
