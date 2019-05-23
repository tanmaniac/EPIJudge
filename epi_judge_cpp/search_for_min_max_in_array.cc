#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
struct MinMax {
  int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
    if (A.empty()) return {0, 0};
    if (A.size() < 2) return {A[0], A[0]};

    MinMax result{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};

    auto compare = [](int a, int b) -> MinMax {
        if (a > b) {
            return {b, a};
        } else {
            return {a, b};
        }
    };
    for (int i = 0; i + 1 < A.size(); i += 2) {
        auto curPair = compare(A[i], A[i + 1]);
        if (curPair.smallest < result.smallest) {
            result.smallest = curPair.smallest;
        }
        if (curPair.largest > result.largest) {
            result.largest = curPair.largest;
        }
    }

    if (A.size() % 2 != 0) {
        result.largest = std::max(result.largest, A.back());
        result.smallest = std::min(result.smallest, A.back());
    }
    return result;
}
template <>
struct SerializationTraits<MinMax> : UserSerTraits<MinMax, int, int> {};

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}
