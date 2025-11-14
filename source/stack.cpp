#include <iostream>

template <typename T>
struct Node {
  T data;
  Node<T> *next;
};

template <typename T>
class Stack {
public:
  Stack() {
    head = nullptr;
    size = 0;
  }

  ~Stack() {
    Node<T> *current = head;
    while (current != nullptr) {
      Node<T> *next = current->next;
      delete current;
      current = next;
    }
  }

  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty");
    }

    size--;
    T data = head->data;
    head = head->next;
    delete head;
    return data;
  }

  void push(T data) {
    size++;
    Node<T> *node = new Node<T>(data);
    node->next = head;
    head = node;
  }

  bool isEmpty() { return size == 0; }

  int getSize() { return size; }

  void print() {
    Node<T> *current = head;
    std::cout << "Stack (size=" << size << "): ";
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

private:
  Node<T> *head;
  int size;
};
