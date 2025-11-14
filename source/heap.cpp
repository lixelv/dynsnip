#include <iostream>
#include <vector>

template <typename T, bool (*Comp)(const T &, const T &)>
class Heap {
public:
  Heap() { std::vector<T> arr; }

  void insert(int val) {
    arr.push_back(val);
    siftUp(arr.size() - 1);
  }

  int popRoot() {
    if (arr.empty()) {
      throw std::out_of_range("Heap is empty");
    }

    int result = arr[0];
    int last = arr.size() - 1;

    std::swap(arr[0], arr[last]);
    arr.pop_back();

    if (!arr.empty()) {
      siftDown(0);
    }

    return result;
  }

  int peek() const {
    if (arr.empty()) {
      throw std::out_of_range("Heap is empty");
    }
    return arr[0];
  }

  bool empty() const { return arr.empty(); }

  int size() const { return static_cast<int>(arr.size()); }

  void clear() { arr.clear(); }

  void print() const {
    print(0, 0);
    std::cout << std::endl;
  }

private:
  std::vector<int> arr;

  void siftUp(int i) {
    while (i > 0) {
      int p = (i - 1) / 2;
      if (Comp(arr[i], arr[p])) {
        std::swap(arr[i], arr[p]);
        i = p;
      } else {
        break;
      }
    }
  }

  void siftDown(int i) {
    int n = static_cast<int>(arr.size());
    while (true) {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      int nest = i;

      if (left < n && Comp(arr[left], arr[nest])) {
        nest = left;
      }
      if (right < n && Comp(arr[right], arr[nest])) {
        nest = right;
      }

      if (nest != i) {
        std::swap(arr[i], arr[nest]);
        i = nest;
      } else {
        break;
      }
    }
  }

  void print(int index, int depth) const {
    if (index >= static_cast<int>(arr.size()))
      return;

    int right = 2 * index + 2;
    int left = 2 * index + 1;

    print(right, depth + 1);

    for (int i = 0; i < depth; ++i) {
      std::cout << "   ";
    }

    std::cout << arr[index] << std::endl;
    print(left, depth + 1);
  }
};

template <typename T> bool minCompare(const T &a, const T &b) { return a < b; }
template <typename T> bool maxCompare(const T &a, const T &b) { return a > b; }

template <typename T = int> using MinHeap = Heap<T, minCompare<T>>;
template <typename T = int> using MaxHeap = Heap<T, maxCompare<T>>;

int main() {
  MaxHeap<int> minHeap;
  minHeap.insert(5);
  minHeap.insert(3);
  minHeap.insert(7);
  minHeap.insert(2);
  minHeap.insert(4);
  minHeap.insert(6);
  minHeap.insert(8);
  minHeap.print();
}