#include <vector>
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
    auto *node = tree.get();
    decltype(node) last = nullptr;

    std::vector<int> traversal;

    while (node != nullptr) {
        if (node->parent == last) {
            // We need to try to go left
            if (node->left != nullptr) {
                last = node;
                node = node->left.get();
            } else /* either this is a leaf or it has a nonempty right subtree */ {
                traversal.push_back(node->data);
                last = node;
                node = (node->right != nullptr) ? node->right.get() : node->parent;
            }
        } else if (node->left.get() == last) {
            // Already finished left subtree so now we need to try to go right
            traversal.push_back(node->data);
            last = node;
            node = (node->right != nullptr) ? node->right.get() : node->parent;
        } else /* Finished both left and right subtrees */ {
            last = node;
            node = node->parent;
        }
    }
    return traversal;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
