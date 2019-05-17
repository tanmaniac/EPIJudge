#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
  std::priority_queue<int, std::vector<int>, std::less<>> lower; // max heap
  std::priority_queue<int, std::vector<int>, std::greater<>> upper; // min heap
  std::vector<double> medians;

  while (sequence_begin != sequence_end) {
      upper.push(*sequence_begin++);
      lower.push(upper.top());
      upper.pop();
      while (lower.size() > upper.size()) {
          upper.push(lower.top());
          lower.pop();
      }

      medians.push_back((upper.size() == lower.size()) ? (upper.top() + lower.top()) / 2.0 : upper.top());
  }
  return medians;
}
vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
