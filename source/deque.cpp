#include <iostream>

template <typename T> struct Node {
  T data;
  Node<T> *next;
  Node<T> *prev;

  Node(T v) {
    data = v;
    next = nullptr;
    prev = nullptr;
  }
};

template <typename T> class Queue {
public:
  Node<T> *head;
  Node<T> *tail;
  int size;
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

  T popBack() {
    if (tail == nullptr) {
      throw std::runtime_error("Deque is empty");
    }

    Node<T> *nodeToDelete = tail;
    T data = tail->data;

    if (head == tail) {
      head = nullptr;
      tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }

    delete nodeToDelete;
    size--;
    return data;
  }

  T popForward() {
    if (head == nullptr) {
      throw std::runtime_error("Deque is empty");
    }

    Node<T> *nodeToDelete = head;
    T data = head->data;

    if (head == tail) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = head->next;
      head->prev = nullptr;
    }

    delete nodeToDelete;
    size--;
    return data;
  }

  void pushBack(T data) {
    Node<T> *node = new Node<T>(data);

    if (tail == nullptr) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
    size++;
  }

  void pushForward(T data) {
    Node<T> *node = new Node<T>(data);

    if (head == nullptr) {
      head = node;
      tail = node;
    } else {
      head->prev = node;
      node->next = head;
      head = node;
    }
    size++;
  }

  void print() {
    Node<T> *current = head;
    std::cout << "Deque (size=" << size << "): ";
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }
};

#include <cassert>

int main() {
  std::cout << "=== Deque Tests ===" << std::endl;

  std::cout << "\n1. Testing single element operations:" << std::endl;
  Queue<int> q1;
  q1.pushBack(42);
  std::cout << "After pushBack(42): ";
  q1.print();

  int val1 = q1.popForward();
  std::cout << "Popped from front: " << val1 << std::endl;
  assert(val1 == 42);
  assert(q1.size == 0);

  std::cout << "\n2. Testing push to both ends:" << std::endl;
  Queue<int> q2;
  q2.pushForward(1);
  q2.pushBack(2);
  q2.pushForward(0);
  std::cout << "After pushes: ";
  q2.print();

  assert(q2.popForward() == 0);
  assert(q2.popBack() == 2);
  assert(q2.popForward() == 1);
  assert(q2.size == 0);

  // Тест 3: Строки
  std::cout << "\n3. Testing with strings:" << std::endl;
  Queue<std::string> strDeque;
  strDeque.pushBack("hello");
  strDeque.pushForward("world");
  strDeque.pushBack("test");

  std::cout << "String deque: ";
  strDeque.print();

  assert(strDeque.popForward() == "world");
  assert(strDeque.popBack() == "test");
  assert(strDeque.popForward() == "hello");

  std::cout << "\n4. Testing mixed operations:" << std::endl;
  Queue<int> q3;
  q3.pushBack(1);
  q3.pushBack(2);
  q3.pushForward(0);

  assert(q3.popForward() == 0);
  assert(q3.popBack() == 2);
  assert(q3.popForward() == 1);
  assert(q3.size == 0);

  std::cout << "\n5. Testing multiple operations:" << std::endl;
  Queue<int> q4;
  for (int i = 0; i < 5; i++) {
    q4.pushBack(i);
  }
  std::cout << "After adding 0-4: ";
  q4.print();

  for (int i = 0; i < 3; i++) {
    q4.popForward();
  }
  std::cout << "After removing 3 from front: ";
  q4.print();

  assert(q4.popForward() == 3);
  assert(q4.popBack() == 4);
  assert(q4.size == 0);

  std::cout << "\n6. Testing reverse order:" << std::endl;
  Queue<int> q5;
  q5.pushForward(3);
  q5.pushForward(2);
  q5.pushForward(1);

  std::cout << "Reverse order: ";
  q5.print();

  assert(q5.popBack() == 3);
  assert(q5.popBack() == 2);
  assert(q5.popBack() == 1);

  std::cout << "\n=== All tests passed! ===" << std::endl;

  return 0;
}