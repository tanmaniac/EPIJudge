#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  int lo = 0;
  int hi = k;

  while (lo <= hi) {
      long long mid = lo + (hi - lo) / 2;
      long long midSq = mid * mid;

      if (midSq == k) {
          return mid;
      } else if (midSq > k) {
          hi = mid - 1;
      } else {
          lo = mid + 1;
      }
  }
  return lo - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
