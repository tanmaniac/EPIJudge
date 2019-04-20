#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

template <typename T>
int getListLength(std::shared_ptr<ListNode<T>> list) {
    int length = 0;
    while (list != nullptr) {
        length++;
        list = list->next;
    }
    return length;
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  int l0Length = getListLength(l0);
  int l1Length = getListLength(l1);

  // Determine which is bigger
  std::shared_ptr<ListNode<int>> longer, shorter;
  if (l0Length > l1Length) {
      longer = l0;
      shorter = l1;
  } else {
      longer = l1;
      shorter = l0;
  }

  // Advance the longer pointer by the difference
  int difference = std::abs(l0Length - l1Length);
  while (difference-- > 0) {
      longer = longer->next;
  }

  // Advance both pointers until they meet
  while (longer != nullptr && shorter != nullptr && longer != shorter) {
      longer = longer->next;
      shorter = shorter->next;
  }
  return shorter;
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
