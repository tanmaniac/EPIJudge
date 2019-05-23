#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool MatrixSearch(const vector<vector<int>>& A, int x) {
    if (A.empty()) return false;

    int rows = A.size();
    int cols = A[0].size();

    int curRow = 0;
    int curCol = cols - 1;

    while (curRow < rows && curCol >= 0) {
        int curVal = A[curRow][curCol];
        if (curVal == x) {
            return true;
        } else if (x > curVal) {
            // It cannot exist in the current row
            curRow++;
        } else {
            // Everything below x in this column is larger than it
            curCol--;
        }
    }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}
