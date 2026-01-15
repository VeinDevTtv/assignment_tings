# Usage Guide - Node Manipulation Assignment

## Quick Reference

### Part 1: Single Node Flip

```cpp
// Build and print
Node* list = buildList();
printList(list);

// Flip middle node
list = flipMiddleNode(list);
printList(list);

// Result: A -> C -> B -> D -> E -> null
```

### Part 2: Double Node Flip

```cpp
// Build and print
DNode* dlist = buildDoublyList();
printDoublyList(dlist);

// Flip middle node
dlist = flipMiddleDoublyNode(dlist);
printDoublyList(dlist);

// Result: A ⇄ C ⇄ B ⇄ D ⇄ E ⇄ null
```

### Part 3: Tree Rotations

```cpp
// Build tree
TreeNode* root = buildTree();
printTree(root);

// Find node and rotate left
TreeNode* nodeX = findNode(root, 'X');
rotateLeft(nodeX, root);
printTree(root);

// Find node and rotate right
TreeNode* nodeY = findNode(root, 'Y');
rotateRight(nodeY, root);
printTree(root);
```

### Part 4: Quad Rotation

```cpp
// Create rotor and demonstrate full cycle
Rotor rotor;
PrintRotor(rotor);

// Or manual rotation:
rotor.print();
int degrees = rotor.rotateClockwise();  // 90°
rotor.print();
```

## Function Signatures

### Part 1
```cpp
Node* buildList();
void printList(Node* head);
Node* flipMiddleNode(Node* head);
```

### Part 2
```cpp
DNode* buildDoublyList();
void printDoublyList(DNode* head);
DNode* flipMiddleDoublyNode(DNode* head);
```

### Part 3
```cpp
TreeNode* buildTree();
void printTree(TreeNode* node, int indent = 0);
void rotateLeft(TreeNode* x, TreeNode*& root);
void rotateRight(TreeNode* y, TreeNode*& root);
TreeNode* findNode(TreeNode* node, char value);
```

### Part 4
```cpp
class Rotor {
    int rotateClockwise();
    void print() const;
    int getDegrees() const;
};
void PrintRotor(Rotor& r);
```

## How It Works

### Middle Node Finding
All flip operations use integer division:
```cpp
int count = 0;
while (temp) { count++; temp = temp->next; }
int middleIndex = count / 2;  // Integer division
```

For list A → B → C → D → E:
- count = 5
- middleIndex = 5 / 2 = 2
- Middle node = C (0-indexed: A=0, B=1, C=2)

### Pointer Rewiring

**Single Flip:**
```
Before: A → B → C → D → E
        ^   ^   ^
        |   |   middle
        beforePrev prev

Rewire:
1. B->next = D     (prev->next = middle->next)
2. C->next = B     (middle->next = prev)
3. A->next = C     (beforePrev->next = middle)

After:  A → C → B → D → E
```

**Double Flip:**
Same logic but maintains both directions (prev/next pointers).

**Tree Rotations:**
Rewires parent, left, and right pointers according to rotation rules.

**Quad Rotation:**
Shifts north→east, east→south, south→west, west→north every 90°.

## Compilation

```cmd
g++ -std=c++17 main.cpp -o node_assignment.exe
node_assignment.exe
```

All implementations are in a single `main.cpp` file for easy submission.
