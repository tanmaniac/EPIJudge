#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (L == nullptr) return L;

  // Find the start'th node
  auto dummy = std::make_shared<ListNode<int>>(0, L);
  auto oneBehind = dummy;
  for (int i = 1; i < start; i++) {
      oneBehind = oneBehind->next;
  }

  auto startNode = oneBehind->next;
  // ???
  for (int i = start; i < finish; i++) {
      auto startNext = startNode->next;
      auto oneAheadNext = oneBehind->next;
      oneBehind->next = startNext;
      startNode->next = startNext->next;
      startNext->next = oneAheadNext;
  }
  return dummy->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
