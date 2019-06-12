#include <memory>
#include <unordered_set>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
    std::unordered_set<BinaryTreeNode<int> *> visited;

    auto *node0Runner = node0.get();
    auto *node1Runner = node1.get();

    while (node0Runner != nullptr || node1Runner != nullptr) {
        if (node0Runner != nullptr) {
            // See if we've visited this node
            auto search = visited.find(node0Runner);
            if (search != visited.end()) {
                // Already seen this node, so this is the LCA
                return node0Runner;
            } else {
                visited.insert(node0Runner);
                node0Runner = node0Runner->parent;
            }
        }

        if (node1Runner != nullptr) {
            auto search = visited.find(node1Runner);
            if (search != visited.end()) {
                return node1Runner;
            } else {
                visited.insert(node1Runner);
                node1Runner = node1Runner->parent;
            }
        }
    }

    return nullptr;
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
  return GenericTestMain(args, "lowest_common_ancestor_close_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
