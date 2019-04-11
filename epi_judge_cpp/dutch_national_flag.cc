#include <array>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
typedef enum { kRed, kWhite, kBlue } Color;

template <typename T>
void swapVals(T& a, T& b) {
    T aVal = a;
    a = b;
    b = aVal;
}

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
  auto& flags = *A_ptr;
  auto pivot = flags[pivot_index];

  int curIdx = 0;
  int last = flags.size() - 1;
  int smallest = 0;
  while (curIdx <= last) {
      if (flags[curIdx] == pivot) {
          curIdx++;
      } else if (flags[curIdx] < pivot) {
          swapVals(flags[smallest++], flags[curIdx++]);
      } else {
          // swap the current last value with the inspected value
          swapVals(flags[curIdx], flags[last--]);
      }
  }
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[colors[i]]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
