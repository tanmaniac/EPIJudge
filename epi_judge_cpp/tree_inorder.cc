#include <memory>
#include <vector>
#include <stack>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree == nullptr) {
        return {};
    }

    std::stack < BinaryTreeNode<int> * > callStack;
    auto *current = tree.get();

    std::vector<int> traversal;

    while (current != nullptr || !callStack.empty()) {
        while (current != nullptr) {
            callStack.push(current);
            current = current->left.get();
        }

        // We're now at the first null left node, so the node we want is at the top of the stack
        auto *top = callStack.top();
        callStack.pop();
        traversal.push_back(top->data);
        current = top->right.get();
    }

    return traversal;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
