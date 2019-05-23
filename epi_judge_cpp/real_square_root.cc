#include "test_framework/generic_test.h"

enum class Ordering {
    smaller, equal, larger
};

template<typename T>
Ordering compare(T lo, T hi) {
    double diff = (lo - hi) / std::max(std::abs(lo), std::abs(hi));
    if (diff < -std::numeric_limits<T>::epsilon()) {
        return Ordering::smaller;
    } else if (diff > std::numeric_limits<T>::epsilon()) {
        return Ordering::larger;
    } else {
        return Ordering::equal;
    }
}
double SquareRoot(double x) {
    double hi, lo;
    if (x < 1) {
        lo = x, hi = 1;
    } else {
        lo = 1;
        hi = x;
    }

    while (compare(lo, hi) != Ordering::equal) {
        double mid = lo + (hi - lo) / 2.0;
        double midSq = mid * mid;
        if (compare(midSq, x) == Ordering::larger) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return lo;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
