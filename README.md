# DynSnip

VSCode extension with C++ snippets for common data structures. Use command `Pick DynSnip` for quick access to list of snippets.

## What's Inside

Six data structures with complete implementations:

- **Binary Search Tree**
- **AVL Tree**
- **Heap**
- **Stack**
- **Queue**
- **Deque**

All templates support generic types and include methods like insert, remove, search, print, etc.

## Installation

### From Release

Download the `.vsix` file from releases and run:

```bash
code --install-extension dynsnip-0.0.4.vsix
```

Or install through VSCode:
- Press `Ctrl+Shift+P`
- Type "Extensions: Install from VSIX"
- Select the downloaded file
- Restart VSCode

### From Source

```bash
git clone https://github.com/your-username/dynsnip
cd dynsnip
code .
```

Press `F5` to test in Extension Development Host.

## Usage

1. Open a `.cpp` file
2. Press `f1` and write `Pick DynSnip`
3. Select and press `Enter`

## Data Structures

### Binary Search Tree

Creates `BSTAbstract<T, Comp>` and `BST<T>` classes with:
- `void insert(T val)`
- `T* search(T val)` 
- `bool remove(T val)`
- `void print()`

### AVL Tree

Self-balancing BST with same methods plus automatic rotations. Guaranteed O(log n) operations.

### Heap

Binary heap with array implementation:
- `void insert(T val)`
- `T popRoot()`
- `T peek()`
- `bool empty()`
- `int size()`
- `void clear()`
- `void print()`

Comes with `MinHeap<T>` and `MaxHeap<T>` type aliases.

### Stack

LIFO linked list implementation:
- `void push(T val)`
- `T pop()`
- `bool isEmpty()`
- `int size()`
- `void print()`

### Queue

FIFO linked list with head and tail pointers:
- `void enqueue(T data)`
- `T dequeue()`
- `bool isEmpty()`
- `int getSize()`
- `void print()`

### Deque

Double-ended queue with doubly-linked list:
- `void pushBack(T data)`
- `void pushForward(T data)`
- `T popBack()`
- `T popForward()`
- `void print()`

## Testing

All snippets are ready to compile and use. They include:
- Generic template support
- Proper memory management
- Exception handling where needed
- Print methods for debugging

Example usage:

```cpp
BST<int> tree;
tree.insert(5);
tree.insert(3);
tree.insert(7);
tree.print();

MinHeap<int> heap;
heap.insert(10);
heap.insert(5);
int min = heap.popRoot(); // 5

Stack<char> stack;
stack.push('a');
char top = stack.pop(); // 'a'
```

## Documentation

See [DOCS.md](docs/DOCS.md) for detailed information about each data structure, time complexities, and method descriptions.

## Building VSIX

```bash
npm install -g vsce
vsce package
```

This creates `dynsnip-0.0.4.vsix` in the current directory.

## License

MIT

## Contributing

Found a bug or want to add more data structures? Open an issue or PR.
