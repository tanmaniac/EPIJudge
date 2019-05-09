#include <string>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

std::unique_ptr<BinaryTreeNode<int>> treeBuilder(const std::vector<int *> &preorder, size_t *start) {
    if (*start > preorder.size()) return nullptr;

    int *val = preorder[*start];
    (*start)++;

    if (val == nullptr) {
        return nullptr;
    } else {
        auto node = std::make_unique<BinaryTreeNode<int>>(*val);
        node->left = treeBuilder(preorder, start);
        node->right = treeBuilder(preorder, start);
        return node;
    }
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
    const vector<int*>& preorder) {
    size_t start = 0;
    return treeBuilder(preorder, &start);
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
