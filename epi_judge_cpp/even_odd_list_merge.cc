#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  if (L == nullptr) return nullptr;
  if (L->next == nullptr) return L; // Already merged

  auto firstEven = L;
  auto firstOdd = L->next;
  auto lastEven = L;
  auto lastOdd = L->next;

  while (lastOdd != nullptr && lastOdd->next != nullptr) {
      auto nextEven = lastOdd->next;
      auto nextOdd = nextEven->next;

      lastEven->next = nextEven;
      lastOdd->next = nextOdd;
      nextEven->next = firstOdd;

      // update pointers
      lastEven = lastEven->next;
      lastOdd = lastOdd->next;
  }
  return firstEven;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
