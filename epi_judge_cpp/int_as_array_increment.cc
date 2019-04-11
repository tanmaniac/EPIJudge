#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  int carry = 1;
  int idx = A.size() - 1;
  while (carry != 0 && idx >= 0) {
      int digit = A[idx] + carry;
      carry = digit / 10;
      A[idx] = digit % 10;
      idx--;
  }
  // handle cases where we add another digit, e.g. 999 -> 1000
  if (carry != 0) {
      A.push_back(0);
      A[0] = 1;
  }

  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
