#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
    int hi = A.size() - 1;
    int lo = 0;
    int result = -1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == k) {
            // Found the target, so set result to mid
            result = mid;
            hi = mid - 1;
        } else if (A[mid] < k) {
            // Go right
            lo = mid + 1;
        } else /* A[mid] > k */ {
            hi = mid - 1;
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
