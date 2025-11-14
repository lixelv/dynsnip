#include <iostream>

template <typename T> struct Node {
  T data;
  Node<T> *next;

  Node(T data, Node<T> *next = nullptr) : data(data), next(next) {}
};

template <typename T> class Queue {
public:
  Queue() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  ~Queue() {
    Node<T> *current = this->head;
    while (current != nullptr) {
      Node<T> *next = current->next;
      delete current;
      current = next;
    }
  }

  void enqueue(T data) {
    size++;
    Node<T> *node = new Node<T>(data);
    if (tail == nullptr) {
      head = tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }

  T dequeue() {
    if (size == 0) {
      throw std::out_of_range("Queue is empty");
    }

    size--;
    T data = head->data;
    Node<T> *oldHead = head;
    head = head->next;
    delete oldHead;

    if (head == nullptr) {
      tail = nullptr;
    }

    return data;
  }

  bool isEmpty() { return size == 0; }

  int getSize() { return size; }

  void print() {
    Node<T> *current = head;
    std::cout << "Queue (size=" << size << "): ";
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

private:
  Node<T> *head;
  Node<T> *tail;
  int size;
};

int main() {
  std::cout << "=== Queue Tests ===" << std::endl;

  Queue<int> q;

  std::cout << "\nTest 1: empty queue" << std::endl;

  std::cout << "\nTest 2: enqueue 1, 2, 3, 4, 5" << std::endl;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.enqueue(4);
  q.enqueue(5);
  q.print();
  std::cout << "isEmpty(): " << (q.isEmpty() ? "true" : "false") << std::endl;
  std::cout << "getSize(): " << q.getSize() << std::endl;

  std::cout << "\nTest 3: dequeue 3 elements" << std::endl;
  std::cout << "dequeue(): " << q.dequeue() << std::endl;
  std::cout << "dequeue(): " << q.dequeue() << std::endl;
  std::cout << "dequeue(): " << q.dequeue() << std::endl;
  q.print();
  std::cout << "getSize(): " << q.getSize() << std::endl;

  std::cout << "\nTest 4: enqueue 6, 7" << std::endl;
  q.enqueue(6);
  q.enqueue(7);
  q.print();
  std::cout << "getSize(): " << q.getSize() << std::endl;

  std::cout << "\nTest 5: dequeue until empty" << std::endl;
  while (!q.isEmpty()) {
    std::cout << "dequeue(): " << q.dequeue() << std::endl;
    q.print();
  }
  std::cout << "isEmpty(): " << (q.isEmpty() ? "true" : "false") << std::endl;
  std::cout << "getSize(): " << q.getSize() << std::endl;

  std::cout << "\nTest 6: dequeue from empty (expect exception)" << std::endl;
  try {
    q.dequeue();
  } catch (const std::exception &e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== Queue Tests Completed ===" << std::endl;
  return 0;
}