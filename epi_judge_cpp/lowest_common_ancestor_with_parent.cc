#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int height(BinaryTreeNode<int>* node) {
    int height = 0;
    while (node->parent != nullptr) {
        height++;
        node = node->parent;
    }
    return height;
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // Get heights of the two nodes
  int height0 = height(node0.get());
  int height1 = height(node1.get());

  auto taller = (height0 > height1) ? node0.get() : node1.get();
  auto shorter = (height0 > height1) ? node1.get() : node0.get();

  int difference = std::abs(height0 - height1);

  while (difference > 0) {
      taller = taller->parent;
      difference--;
  }

  while (taller != shorter) {
      taller = taller->parent;
      shorter = shorter->parent;
  }

  return taller;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
