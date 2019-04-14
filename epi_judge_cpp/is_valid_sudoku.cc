#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
bool noDuplicates(const std::vector<std::vector<int>>& matrix, int startRow, int startCol, int endRow, int endCol) {
    auto size =  matrix.size();
    std::unordered_set<int> contained;

    for (int row = startRow; row < endRow; row++) {
        for (int col = startCol; col < endCol; col++) {
            auto value = matrix[row][col];
            if (value != 0 && contained.count(value) == 1) {
                return false;
            }
            contained.insert(matrix[row][col]);
        }
    }

    return true;
}
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
    auto boardSize = partial_assignment.size();
  // Check rows
  for (int row = 0; row < boardSize; row++) {
      if (!noDuplicates(partial_assignment, row, 0, row + 1, boardSize)) {
          return false;
      }
  }

  // Check columns
  for (int col = 0; col < boardSize; col++) {
      if (!noDuplicates(partial_assignment, 0, col, boardSize, col + 1)) {
          return false;
      }
  }

  // Check blocks
  int blockSize = std::sqrt(boardSize);
  for (int row = 0; row < boardSize; row += blockSize) {
      for (int col = 0; col < boardSize; col += blockSize) {
          if (!noDuplicates(partial_assignment, row, col, row + blockSize, col + blockSize)) {
              return false;
          }
      }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
