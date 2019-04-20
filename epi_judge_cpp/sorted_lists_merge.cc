#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  auto merged = std::make_shared<ListNode<int>>(-1);
  auto sentinel = merged;
  while (L1 != nullptr || L2 != nullptr) {
      auto temp = std::make_shared<ListNode<int>>();
      if (L1 == nullptr) {
          temp->data = L2->data;
          L2 = L2->next;
      } else if (L2 == nullptr) {
          temp->data = L1->data;
          L1 = L1->next;
      } else /*neither are null*/ {
          if (L1->data < L2->data) {
              temp->data = L1->data;
              L1 = L1->next;
          } else {
              temp->data = L2->data;
              L2 = L2->next;
          }
      }
      sentinel->next = temp;
      sentinel = sentinel->next;
  }
  return merged->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
