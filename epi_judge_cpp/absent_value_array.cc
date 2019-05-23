#include <stdexcept>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::invalid_argument;
using std::vector;

int FindMissingElement(vector<int>::const_iterator stream_begin,
                       const vector<int>::const_iterator& stream_end) {
    auto begin = stream_begin;
    unsigned int numBuckets = 1 << 16;
    std::vector<unsigned int> msbList(numBuckets, 0);
    while (begin != stream_end) {
        int msb = (*begin) >> 16;
        msbList[msb]++;
        begin++;
    }

    const int maxValsPerBucket = 1 << 16;
    int candidateBucket = 0;
    for (int i = 0; i < numBuckets; i++) {
        if (msbList[i] < maxValsPerBucket) {
            candidateBucket = i;
            break;
        }
    }

    // Second pass - look for missing
    std::bitset<maxValsPerBucket> potentiallyMissing;

    for (begin = stream_begin; begin != stream_end; begin++) {
        int lsb = (*begin) & 0xFFFF;    // bottom 16 bits
        potentiallyMissing.set(lsb);
    }

    for (int i = 0; i < potentiallyMissing.size(); i++) {
        if (!potentiallyMissing[i]) {
            // definitely missing! Reconstruct the IP address
            int msb = candidateBucket;
            int lsb = i;
            return (msb << 16) | lsb;
        }
    }

    return 0;
}
int FindMissingElementWrapper(const vector<int>& stream) {
  try {
    return FindMissingElement(cbegin(stream), cend(stream));
  } catch (invalid_argument&) {
    throw TestFailure("Unexpected no_missing_element exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "absent_value_array.cc",
                         "absent_value_array.tsv", &FindMissingElementWrapper,
                         DefaultComparator{}, param_names);
}
