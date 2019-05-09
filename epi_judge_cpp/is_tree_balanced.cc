#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int balancedHelper(const BinaryTreeNode<int>* root) {
    if (root == nullptr) {
        return 0;
    } else if (root->left == nullptr && root->right == nullptr) {
        // It's a leaf
        return 1;
    }

    int leftDepth = balancedHelper(root->left.get());
    int rightDepth = balancedHelper(root->right.get());
    if (leftDepth == -1 || rightDepth == -1 || std::abs(leftDepth - rightDepth) > 1) {
        // Either this node or a child is unbalanced
        return -1;
    }

    return 1 + std::max(leftDepth, rightDepth);
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return balancedHelper(tree.get()) != -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
