#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int sumHelper(const std::unique_ptr<BinaryTreeNode<int>> &root, int runningSum) {
    if (root == nullptr) {
        return 0;
    } else if (root->left == nullptr && root->right == nullptr) {
        return (runningSum << 1) + root->data;
    }

    runningSum = (runningSum << 1) + root->data;
    int mySum = sumHelper(root->left, runningSum) + sumHelper(root->right, runningSum);
    return mySum;
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>> &tree) {
    return sumHelper(tree, 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
