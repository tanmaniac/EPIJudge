#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool symmetricHelper(const BinaryTreeNode<int> *const left, const BinaryTreeNode<int> *const right) {
    if (left == nullptr && right == nullptr) {
        return true;
    } else if ((left == nullptr) != (right == nullptr)) {
        return false;
    }

    if (left->data != right->data) {
        return false;
    }

    return symmetricHelper(left->left.get(), right->right.get()) &&
           symmetricHelper(left->right.get(), right->left.get());
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>> &tree) {
    if (tree == nullptr) return true;
    return symmetricHelper(tree->left.get(), tree->right.get());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
