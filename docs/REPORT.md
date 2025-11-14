# Report on VSCode Plugin Development

**Author:** Simeon Efremenko\
**Plugin:** DynSnip - Dynamic Data Structures Snippets for C++

## 1. Introduction

DynSnip is a VSCode snippet extension providing template implementations for common dynamic data structures in C++ (BST, AVL Tree, Heap, Stack, Queue, Deque).

**Goal:** Create a practical code snippet collection.

---

## 2. VSCode Extension Architecture

### 2.1. Core Components

VSCode uses a modular architecture with three main parts:

```
┌────────────────────────────────────────────┐
│         VSCode Main Process                │
│  ┌──────────────┐    ┌──────────────────┐  │
│  │ Editor Core  │◄──►│ Extension Host   │  │
│  │              │    │   (Node.js)      │  │
│  └──────────────┘    │  ┌────────────┐  │  │
│                      │  │ Extensions │  │  │
│                      │  └────────────┘  │  │
│                      └──────────────────┘  │
└────────────────────────────────────────────┘
```

- **Main Process** - Electron-based UI
- **Extension Host** - Isolated Node.js process for extensions
- **Extension API** - Communication layer

### 2.2. Snippet Extensions

Snippet extensions are declarative (no code needed):

| Component | Purpose |
|-----------|---------|
| `package.json` | Extension manifest |
| `snippets/*.json` | Snippet definitions |
| Contribution Points | Register snippets with VSCode |

---

## 3. Implementation

### 3.1. Project Structure

```
dynsnip/
├── package.json
├── README.md
├── snippets/
│   └── snippets.code-snippets
├── docs/
│   ├── docs.typ
│   ├── docs.pdf
│   ├── DOCS.md
│   ├── REPORT.md
│   └── TASK.md
└── source/
    ├── alv-tree.cpp
    ├── bs-tree.cpp
    ├── deque.cpp
    ├── heap.cpp
    ├── queue.cpp
    └── stack.cpp
```

### 3.2. Extension Manifest

```json
{
  "name": "dynsnip",
  "displayName": "DynSnip",
  "contributes": {
    "snippets": [
      {
        "language": "cpp",
        "path": "./snippets/snippets.code-snippets"
      }
    ]
  }
}
```

**Key fields:**
- `contributes.snippets` - Declares snippet files
- `language` - Target language (cpp)
- `path` - Snippet file location

### 3.3. Snippet Format

Each snippet follows this structure:

```json
{
  "Snippet Name": {
    "prefix": ["trigger1", "trigger2"],
    "body": ["code line 1", "code line 2"],
    "description": "What this snippet does"
  }
}
```

### 3.4. Implemented Data Structures

| Structure | Triggers | Key Operations |
|-----------|----------|----------------|
| Binary Search Tree | `bst`, `binsearchtree` | insert, search, remove |
| AVL Tree | `avltree`, `avl` | insert, search, remove, auto-balance |
| Heap | `heap`, `minheap`, `maxheap` | insert, popRoot, peek |
| Stack | `stack`, `stk` | push, pop, isEmpty |
| Queue | `queue`, `que` | enqueue, dequeue |
| Deque | `deque`, `dq` | pushBack, pushForward, popBack, popForward |

---

## 4. How It Works

### User Workflow

```
Type trigger (e.g., "bst")
        ↓
Visual Studio Code shows snippet
        ↓
Press Tab/Enter
        ↓
Code inserted with placeholders
        ↓
Navigate with Tab key
```

### Development Workflow

```
1. Create snippet JSON definitions
2. Configure package.json
3. Press F5 to test
4. Verify in Extension Development Host
5. Install/Publish
```

---

## 5. Advantages

**No runtime code** - Pure JSON configuration  
**Zero performance overhead** - Built-in VSCode feature  
**Easy maintenance** - Update snippets without code changes  
**Language-scoped** - Only appears in C++ files  
**Small package size** - Efficient distribution  

---

## 6. Conclusion

The project demonstrates:
- VSCode's contribution point system for declarative extensions
- Snippet mechanism for code template insertion
- Practical tool for C++ development with common data structures

**Repository:** https://github.com/lixelv/dynsnip  
**Documentation:** See `DOCUMENTATION.md`
