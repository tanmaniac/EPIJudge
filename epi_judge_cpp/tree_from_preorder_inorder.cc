#include <vector>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

#include <unordered_map>
using std::vector;

struct SliceIndices {
    int pLeft, pRight, iLeft, iRight;
};

std::unique_ptr<BinaryTreeNode<int>>
treeBuilder(const std::unordered_map<int, int> &traversalToIndices, const SliceIndices &slices,
            const std::vector<int> &preorder,
            const std::vector<int> &inorder) {
    if (slices.pRight <= slices.pLeft || slices.iRight <= slices.iLeft) {
        return nullptr;
    }

    // The first value in the preorder traversal is the root of the tree
    int root = preorder[slices.pLeft];
    int inorderRootIdx = traversalToIndices.at(root);
    int leftSize = inorderRootIdx - slices.iLeft;

    // If preorder/inorder is a single value, then this is a leaf
    if (slices.pRight - slices.pLeft == 1) {
        auto node = std::make_unique<BinaryTreeNode<int>>(root);
        return node;
    } else {
        auto node = std::make_unique<BinaryTreeNode<int>>(root);
        // Left subtree
        {
            int iLeft = slices.iLeft;
            int iRight = inorderRootIdx;
            int pLeft = slices.pLeft + 1;
            int pRight = slices.pLeft + 1 + leftSize;
            node->left = treeBuilder(traversalToIndices, {pLeft, pRight, iLeft, iRight}, preorder, inorder);
        }
        // Right subtree
        {
            int iLeft = inorderRootIdx + 1;
            int iRight = slices.iRight;
            int pLeft = slices.pLeft + 1 + leftSize;
            int pRight = slices.pRight;
            node->right = treeBuilder(traversalToIndices, {pLeft, pRight, iLeft, iRight}, preorder, inorder);
        }
        return node;
    }
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
    if (preorder.empty()) {
        return nullptr;
    }

    // Build the map inorder traversal values -> indices in the inorder traversal
    std::unordered_map<int, int> traversalToIndices;
    for (int i = 0; i < inorder.size(); i++) {
        traversalToIndices.insert({inorder[i], i});
    }

    return treeBuilder(traversalToIndices, {0, int(preorder.size()), 0, int(inorder.size())}, preorder, inorder);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
