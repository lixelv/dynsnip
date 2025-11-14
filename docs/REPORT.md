# Report on VSCode Plugin Development

**Author:** Simeon Efremenko\
**Plugin:** DynSnip - Dynamic Data Structures Snippets for C++

## 1. Introduction

DynSnip is a VSCode command snippet selection extension providing template implementations for common dynamic data structures in C++ (BST, AVL Tree, Heap, Stack, Queue, Deque).

**Goal:** Create a practical code snippet collection.

---

## 1.1. Architecture

![alt text](diagram.png)

---

## 2. VSCode Extension Architecture

Snippet extensions are declarative (no code needed):

| Component | Purpose |
|-----------|---------|
| `package.json` | Extension manifest |
| `src/extension.ts` | Main extention code |
| `src/snippets.ts` | Snippet definitions |
| Contribution Points | Register snippets with VSCode |

---

## 3. Implementation

### 3.1. Project Structure

```
dynsnip/
├── package.json
├── README.md
├── src/
│   ├── extension.ts
│   └── snippets.ts
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

| Structure | Key Operations |
|-----------|----------------|
| Binary Search Tree | insert, search, remove |
| AVL Tree | insert, search, remove, auto-balance |
| Heap | insert, popRoot, peek |
| Stack | push, pop, isEmpty |
| Queue | enqueue, dequeue |
| Deque | pushBack, pushForward, popBack, popForward |

---

## 4. How It Works

### User Workflow

```
Press f1, select "Pick DynSnip"
        
Visual Studio Code shows list of snippets
        
Select snippet, press enter
```

### Development Workflow

```
1. Create snippets in cpp
2. Configure package.json
3. Create extention.ts and snippets.ts
4. Press F5 to test
5. Install and test
```

---

## 5. Conclusion

The project demonstrates:
- VSCode's contribution point system for declarative extensions
- Snippet mechanism for code template insertion
- Practical tool for C++ development with common data structures

**Repository:** https://github.com/lixelv/dynsnip  
**Documentation:** See `DOCS.md`
