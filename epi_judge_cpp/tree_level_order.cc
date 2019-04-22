#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  std::vector<std::vector<int>> traversal;
  if (tree == nullptr) {
      return traversal;
  }

  std::queue<BinaryTreeNode<int>*> toTraverse;
  toTraverse.push(tree.get());

  while (!toTraverse.empty()) {
      // Push the entire traversal queue into a new entry onto a new queue
      std::queue<BinaryTreeNode<int>*> curLevel;
      while (!toTraverse.empty()) {
          if (toTraverse.front() != nullptr) {
              curLevel.push(toTraverse.front());
          }
          toTraverse.pop();
      }

      std::vector<int> curLevelVals;
      curLevelVals.reserve(curLevel.size());
      while (!curLevel.empty()) {
          curLevelVals.push_back(curLevel.front()->data);
          toTraverse.push(curLevel.front()->left.get());
          toTraverse.push(curLevel.front()->right.get());
          curLevel.pop();
      }
      if (!curLevelVals.empty()) traversal.push_back(curLevelVals);
  }

  return traversal;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
