#include <iostream>

template <typename T>
struct Node {
  T val;
  Node *left = nullptr;
  Node *right = nullptr;
  Node(T v) : val(v) {}
};

template <typename T, bool (*Comp)(const T &, const T &)>
class BSTAbstract {
public:
  BSTAbstract() { root = nullptr; }

  ~BSTAbstract() { clear(root); }

  void insert(T val) { insertNode(root, val); }
  T *search(T val) { return searchNode(root, val); }
  bool remove(T val) { return removeNode(root, val); }
  void clear() {
    clear(root);
    root = nullptr;
  }

  void print() {
    std::cout << "Tree structure:" << std::endl;
    print(root, 0);
    std::cout << std::endl;
  }

private:
  Node<T> *root;

  int compare(T a, T b) { return Comp(a, b) ? -1 : (Comp(b, a) ? 1 : 0); }

  void insertNode(Node<T>*  &node, T val) {
    if (node == nullptr) {
      node = new Node<T>(val);
      return;
    }

    int r = compare(val, node->val);
    if (r <= 0) {
      insertNode(node->left, val);
    } else {
      insertNode(node->right, val);
    }
  }

  T *searchNode(Node<T>*  node, T val) {
    if (node == nullptr) {
      return nullptr;
    }

    int r = compare(val, node->val);

    if (r < 0) {
      return searchNode(node->left, val);
    } else if (r > 0) {
      return searchNode(node->right, val);
    } else {
      return &(node->val);
    }
  }

  bool removeNode(Node<T> *&node, T val) {
    if (node == nullptr) {
      return false;
    }

    int r = compare(val, node->val);

    if (r < 0) {
      return removeNode(node->left, val);
    } else if (r > 0) {
      return removeNode(node->right, val);
    } else {
      if (node->left == nullptr && node->right == nullptr) {
        delete node;
        node = nullptr;
      } else if (node->left == nullptr) {
        Node<T> *temp = node;
        node = node->right;
        delete temp;
      } else if (node->right == nullptr) {
        Node<T> *temp = node;
        node = node->left;
        delete temp;
      } else {
        Node<T> *successor = findMin(node->right);
        node->val = successor->val;
        removeNode(node->right, successor->val);
      }
      return true;
    }
  }

  Node<T> *findMin(Node<T> *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  void print(Node<T>* node, int depth) {
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

  void clear(Node<T>*  node) {
    if (!node)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
};

template <typename T> bool lessCompare(const T &a, const T &b) { return a < b; }
template <typename T> using BST = BSTAbstract<T, lessCompare<T>>;

int main() {
  std::cout << "=== BST Test ===" << std::endl;

  // Создаем дерево
  BST<int> bst;

  // Тест 1: Вставка элементов
  std::cout << "\n1. Inserting elements: 5, 3, 7, 2, 4, 6, 8" << std::endl;
  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  bst.insert(2);
  bst.insert(4);
  bst.insert(6);
  bst.insert(8);
  bst.print();

  // Тест 2: Поиск элементов
  std::cout << "\n2. Searching for elements:" << std::endl;
  std::cout << "Search 4: "
            << (bst.search(4) != nullptr ? "Found" : "Not found") << std::endl;
  std::cout << "Search 10: "
            << (bst.search(10) != nullptr ? "Found" : "Not found") << std::endl;

  // Тест 3: Удаление листа
  std::cout << "\n3. Removing leaf node (2):" << std::endl;
  bst.remove(2);
  bst.print();

  // Тест 4: Удаление узла с одним потомком
  std::cout << "\n4. Removing node with one child (7):" << std::endl;
  bst.remove(7);
  bst.print();

  // Тест 5: Удаление узла с двумя потомками (корня)
  std::cout << "\n5. Removing node with two children (root 5):" << std::endl;
  bst.remove(5);
  bst.print();

  // Тест 6: Удаление несуществующего элемента
  std::cout << "\n6. Removing non-existent element (100):" << std::endl;
  bool result = bst.remove(100);
  std::cout << "Result: " << (result ? "Success" : "Failed (expected)")
            << std::endl;
  bst.print();

  // Тест 7: Поиск после удалений
  std::cout << "\n7. Searching after deletions:" << std::endl;
  std::cout << "Search 6: "
            << (bst.search(6) != nullptr ? "Found" : "Not found") << std::endl;
  std::cout << "Search 5: "
            << (bst.search(5) != nullptr ? "Found" : "Not found") << std::endl;

  // Тест 8: Добавление новых элементов после удалений
  std::cout << "\n8. Adding new elements after deletions: 1, 9" << std::endl;
  bst.insert(1);
  bst.insert(9);
  bst.print();

  // Тест 9: Удаление всех элементов по одному
  std::cout << "\n9. Removing all elements one by one:" << std::endl;
  int elements[] = {6, 3, 4, 8, 1, 9};
  for (int elem : elements) {
    std::cout << "Removing " << elem << ":" << std::endl;
    bst.remove(elem);
    bst.print();
  }

  // Тест 10: Попытка удаления из пустого дерева
  std::cout << "\n10. Removing from empty tree:" << std::endl;
  result = bst.remove(5);
  std::cout << "Result: " << (result ? "Success" : "Failed (expected)")
            << std::endl;

  // Тест 11: Создание нового дерева и проверка корректности
  std::cout << "\n11. Creating new tree and testing complex removals:"
            << std::endl;
  BST<int> bst2;
  bst2.insert(10);
  bst2.insert(5);
  bst2.insert(15);
  bst2.insert(3);
  bst2.insert(7);
  bst2.insert(12);
  bst2.insert(17);
  bst2.insert(1);
  bst2.insert(4);
  bst2.insert(6);
  bst2.insert(8);
  bst2.insert(11);
  bst2.insert(13);
  bst2.insert(16);
  bst2.insert(18);

  std::cout << "Initial tree:" << std::endl;
  bst2.print();

  // Удаляем сложные случаи
  std::cout << "After removing 5 (node with two children):" << std::endl;
  bst2.remove(5);
  bst2.print();

  std::cout << "After removing 15 (node with two children):" << std::endl;
  bst2.remove(15);
  bst2.print();

  std::cout << "\n=== All tests completed ===" << std::endl;

  return 0;
}