#include <memory>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

// too stupid to figure this out I should just give up
struct LCAResult {
    int numContained = 0;
    BinaryTreeNode<int>* lca = nullptr;
};

LCAResult lcaHelper(BinaryTreeNode<int>* root, BinaryTreeNode<int>* node0, BinaryTreeNode<int>* node1) {
    if (root == nullptr) {
        return {0, nullptr};
    }

    LCAResult left = lcaHelper(root->left.get(), node0, node1);
    if (left.numContained == 2) {
        // Already found
        return left;
    }

    LCAResult right = lcaHelper(root->right.get(), node0, node1);
    if (right.numContained == 2) {
        // Already found and also I want to die
        return right;
    }

    int numContained = left.numContained + right.numContained + (root->data == node0->data) + (root->data == node1->data);
    return {numContained, (numContained == 2) ? root : nullptr};
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  return lcaHelper(tree.get(), node0.get(), node1.get()).lca;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
