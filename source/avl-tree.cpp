#include <iostream>

template <typename T>
struct Node {
  T val;
  Node *left = nullptr;
  Node *right = nullptr;
  int height = 1;

  Node(T v) : val(v) {}
};

template <typename T, bool (*Comp)(const T &, const T &)>
class AVLAbstract {
public:
  AVLAbstract() { root = nullptr; }

  ~AVLAbstract() { clear(root); }

  void insert(T val) { root = insertNode(root, val); }
  T *search(T val) { return searchNode(root, val); }
  bool remove(T val) {
    bool removed = false;
    root = removeNode(root, val, removed);
    return removed;
  }

  void print() {
    print(root, 0);
    std::cout << std::endl;
  }

private:
  Node<T> *root;

  int compare(T a, T b) { return Comp(a, b) ? -1 : (Comp(b, a) ? 1 : 0); }

  int getHeight(Node<T> *node) { return node ? node->height : 0; }

  int getBalance(Node<T> *node) {
    if (!node)
      return 0;
    return getHeight(node->left) - getHeight(node->right);
  }

  void updateHeight(Node<T> *node) {
    if (!node)
      return;
    int hl = getHeight(node->left);
    int hr = getHeight(node->right);
    node->height = std::max(hl, hr) + 1;
  }

  Node<T> *rotateRight(Node<T> *y) {
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  Node<T> *rotateLeft(Node<T> *x) {
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  Node<T> *balanceNode(Node<T> *node) {
    if (!node)
      return node;

    updateHeight(node);
    int balance = getBalance(node);

    // LL
    if (balance > 1 && getBalance(node->left) >= 0) {
      return rotateRight(node);
    }

    // LR
    if (balance > 1 && getBalance(node->left) < 0) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }

    // RR
    if (balance < -1 && getBalance(node->right) <= 0) {
      return rotateLeft(node);
    }

    // RL
    if (balance < -1 && getBalance(node->right) > 0) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }

    return node;
  }

  Node<T> *insertNode(Node<T> *node, T val) {
    if (!node) {
      return new Node<T>(val);
    }

    int r = compare(val, node->val);
    if (r < 0) {
      node->left = insertNode(node->left, val);
    } else if (r > 0) {
      node->right = insertNode(node->right, val);
    } else {
      return node;
    }

    return balanceNode(node);
  }

  T *searchNode(Node<T> *node, T val) {
    if (!node)
      return nullptr;

    int r = compare(val, node->val);
    if (r < 0)
      return searchNode(node->left, val);
    if (r > 0)
      return searchNode(node->right, val);
    return &(node->val);
  }

  Node<T> *findMin(Node<T> *node) {
    while (node && node->left) {
      node = node->left;
    }
    return node;
  }

  Node<T> *removeNode(Node<T> *node, T val, bool &removed) {
    if (!node) {
      removed = false;
      return nullptr;
    }

    int r = compare(val, node->val);
    if (r < 0) {
      node->left = removeNode(node->left, val, removed);
    } else if (r > 0) {
      node->right = removeNode(node->right, val, removed);
    } else {
      removed = true;
      if (!node->left && !node->right) {
        delete node;
        return nullptr;
      } else if (!node->left) {
        Node<T> *temp = node->right;
        delete node;
        return temp;
      } else if (!node->right) {
        Node<T> *temp = node->left;
        delete node;
        return temp;
      } else {
        Node<T> *successor = findMin(node->right);
        node->val = successor->val;
        node->right = removeNode(node->right, successor->val, removed);
      }
    }

    return balanceNode(node);
  }

  void print(Node<T> *node, int depth) {
    if (node == nullptr) {
      return;
    }

    print(node->right, depth + 1);

    for (int i = 0; i < depth; i++) {
      std::cout << "   ";
    }
    std::cout << node->val << std::endl;

    print(node->left, depth + 1);
  };

  void clear(Node<T> *node) {
    if (!node)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
};

template <typename T> bool lessCompare(const T &a, const T &b) { return a < b; }
template <typename T> using AVLTree = AVLAbstract<T, lessCompare<T>>;

int main() {
  std::cout << "=== AVL Test ===" << std::endl;

  AVLTree<int> avl;

  std::cout << "\n1. Inserting elements: 5, 3, 7, 2, 4, 6, 8" << std::endl;
  avl.insert(5);
  avl.insert(3);
  avl.insert(7);
  avl.insert(2);
  avl.insert(4);
  avl.insert(6);
  avl.insert(8);
  avl.print();

  std::cout << "\n2. Searching for elements:" << std::endl;
  std::cout << "Search 4: "
            << (avl.search(4) != nullptr ? "Found" : "Not found") << std::endl;
  std::cout << "Search 10: "
            << (avl.search(10) != nullptr ? "Found" : "Not found") << std::endl;

  std::cout << "\n3. Removing leaf node (2):" << std::endl;
  avl.remove(2);
  avl.print();

  std::cout << "\n4. Removing node with one child (7):" << std::endl;
  avl.remove(7);
  avl.print();

  std::cout << "\n5. Removing node with two children (root 5):" << std::endl;
  avl.remove(5);
  avl.print();

  std::cout << "\n6. Removing non-existent element (100):" << std::endl;
  bool result = avl.remove(100);
  std::cout << "Result: " << (result ? "Success" : "Failed (expected)")
            << std::endl;
  avl.print();

  std::cout << "\n7. Searching after deletions:" << std::endl;
  std::cout << "Search 6: "
            << (avl.search(6) != nullptr ? "Found" : "Not found") << std::endl;
  std::cout << "Search 5: "
            << (avl.search(5) != nullptr ? "Found" : "Not found") << std::endl;

  std::cout << "\n8. Adding new elements after deletions: 1, 9" << std::endl;
  avl.insert(1);
  avl.insert(9);
  avl.print();

  std::cout << "\n9. Removing all elements one by one:" << std::endl;
  int elements[] = {6, 3, 4, 8, 1, 9};
  for (int elem : elements) {
    std::cout << "Removing " << elem << ":" << std::endl;
    avl.remove(elem);
    avl.print();
  }

  std::cout << "\n10. Removing from empty tree:" << std::endl;
  result = avl.remove(5);
  std::cout << "Result: " << (result ? "Success" : "Failed (expected)")
            << std::endl;

  std::cout << "\n11. Creating new AVL tree and testing complex operations:"
            << std::endl;
  AVLTree<int> avl2;
  int elems2[] = {10, 5, 15, 3, 7, 12, 17, 1, 4, 6, 8, 11, 13, 16, 18};
  for (int x : elems2)
    avl2.insert(x);

  std::cout << "Initial tree:" << std::endl;
  avl2.print();

  std::cout << "After removing 5 (node with two children):" << std::endl;
  avl2.remove(5);
  avl2.print();

  std::cout << "After removing 15 (node with two children):" << std::endl;
  avl2.remove(15);
  avl2.print();

  std::cout << "\n12. Inserting sorted sequence into new tree (1..15):"
            << std::endl;
  AVLTree<int> avl3;
  for (int i = 1; i <= 15; ++i) {
    avl3.insert(i);
  }
  avl3.print();
  std::cout << "Height should be O(log n), not a straight line." << std::endl;

  std::cout << "\n=== All AVL tests completed ===" << std::endl;
  return 0;
}
