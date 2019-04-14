#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  // Set all non-primes first
  std::vector<bool> isPrime(n, true);
  std::vector<int> primes;
  for (int i = 0; i <= n; i++) {
      if (i <= 1) {
          isPrime[i] = false;
      }
      if (isPrime[i]) {
          primes.push_back(i);
          // Set all multiples to false
          for (int mult = 2; mult * i <= n; mult++) {
              isPrime[mult * i] = false;
          }
      }
  }
  return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
