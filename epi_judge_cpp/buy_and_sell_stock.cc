#include <vector>
#include <limits>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  if (prices.empty()) return 0;

  double minElement = std::numeric_limits<double>::max();
  double bestProfit = std::numeric_limits<double>::min();
  for (const auto& price : prices) {
      minElement = std::min(minElement, price);
      bestProfit = std::max(bestProfit, price - minElement);
  }

  return bestProfit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
