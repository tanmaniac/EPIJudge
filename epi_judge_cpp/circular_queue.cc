#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

// This isn't even a circular queue wtf
class Queue {
public:
    Queue(size_t capacity) : _entries(capacity), _head(0), _tail(0), _count(0) {}

    void Enqueue(int x) {
        if (_count == _entries.size()) {
            std::rotate(_entries.begin(), _entries.begin() + _head, _entrie s.end());
            _head = 0;
            _tail = _count;
            _entries.resize(_entries.size() * 2);
        }

        _entries[_tail] = x;
        _tail = (_tail + 1) % _entries.size(), ++_count;
    }

    int Dequeue() {
        int result = _entries[_head];
        _head = (_head + 1) % _entries.size();
        _count--;
        // Resize
        if (_count <= float(_entries.size()) / 4) {
            std::rotate(_entries.begin(), _entries.begin() + _head, _entries.end());
            _head = 0;
            _tail = _count;
            _entries.resize(std::ceil(float(_entries.size()) / 2));
        }
        return result;
    }

    int Size() const {
        return _count;
    }

private:
    std::vector<int> _entries;
    int _head, _tail, _count;
};

struct QueueOp {
  enum { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = kConstruct;
    } else if (op_string == "dequeue") {
      op = kDequeue;
    } else if (op_string == "enqueue") {
      op = kEnqueue;
    } else if (op_string == "size") {
      op = kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case kEnqueue:
        q.Enqueue(argument);
        break;
      case kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

template <>
struct SerializationTraits<QueueOp> : UserSerTraits<QueueOp, std::string, int> {
};

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
