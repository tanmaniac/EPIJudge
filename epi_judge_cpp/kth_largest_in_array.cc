#include <vector>
#include <random>
#include "test_framework/generic_test.h"
using std::vector;

template<typename T>
int partition(std::vector<T> &input, int pivotIdx, int left, int right) {
    int pivot = input[pivotIdx];
    int newPivotIdx = left;
    std::swap(input[pivotIdx], input[right]);
    for (int i = left; i < right; i++) {
        if (input[i] > pivot) {
            std::swap(input[i], input[newPivotIdx++]);
        }
    }
    std::swap(input[newPivotIdx], input[right]);
    return newPivotIdx;
}

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
    auto &A = *A_ptr;

    std::default_random_engine gen((std::random_device())());
    int left = 0;
    int right = A.size() - 1;

    while (left <= right) {
        int pivotIdx = std::uniform_int_distribution<>{left, right}(gen);
        int movedTo = partition(A, pivotIdx, left, right);
        if (movedTo == k - 1) {
            return A[movedTo];
        } else if (movedTo < k - 1) {
            // Partitioned array is more heavily weighted on the right side, so we search right
            left = movedTo + 1;
        } else {
            right = movedTo - 1;
        }
    }
    return -1;
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
