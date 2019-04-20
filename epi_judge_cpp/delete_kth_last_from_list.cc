#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
  auto ahead = L;
  auto oneBeforeTarget = std::make_shared<ListNode<int>>(0, L);
  auto dummy = oneBeforeTarget;
  while (k-- > 0) {
      ahead = ahead->next;
  }

  // Advance both pointers until ahead is null
  while (ahead != nullptr) {
      ahead = ahead->next;
      oneBeforeTarget = oneBeforeTarget->next;
  }

  // Remove the one after oneBeforeTarget, which is the target
  oneBeforeTarget->next = oneBeforeTarget->next->next;

  return dummy->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
