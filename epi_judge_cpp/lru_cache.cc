#include <vector>
#include <unordered_map>
#include <list>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache {
 public:
    using Map = std::unordered_map<int, std::pair<int, std::list<int>::iterator>>;

    LruCache(size_t capacity) : _capacity(capacity) {}

  int Lookup(int isbn) {
      auto search = _cache.find(isbn);
      if (search == _cache.end()) {
          return -1;
      } else {
          int price = search->second.first;
          swapToFront(search);
          return price;
      }
  }

  void Insert(int isbn, int price) {
      // Check if the entry already exists
      auto search = _cache.find(isbn);
      if (search == _cache.end()) {
          if (_cache.size() >= _capacity) {
              _cache.erase(_recentlyUsed.back());
              _recentlyUsed.pop_back();
          }

          // Insert into the LRU queue and the cache map
          _recentlyUsed.push_front(isbn);
          _cache.insert({isbn, {price, _recentlyUsed.begin()}});
      } else {
          // Already exists, so just update the LRU queue
          swapToFront(search);
      }
  }

    bool Erase(int isbn) {
        auto search = _cache.find(isbn);
        if (search == _cache.end()) {
            return false;
        } else {
            _recentlyUsed.erase(search->second.second);
            _cache.erase(search);
            return true;
        }
    }

private:
    void swapToFront(Map::iterator& iter) {
        int isbn = iter->first;
        _recentlyUsed.erase(iter->second.second);
        _recentlyUsed.push_front(isbn);
        iter->second.second = _recentlyUsed.begin();
    }

    size_t _capacity;
    std::list<int> _recentlyUsed;
    Map _cache;
};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &RunTest,
                         DefaultComparator{}, param_names);
}
