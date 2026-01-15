# Node Manipulation Assignment - Usage Guide

## Overview

This implementation provides **TWO approaches** for each part:

1. **Free Functions** - Matching the exact signatures in the assignment specification
2. **OOP Classes** - Proper object-oriented design with encapsulation

## Part 1: Single Node Flip

### Free Functions (Spec-Compliant)
```cpp
// Build list as shown in assignment
Node* buildList();

// Print function matching assignment signature  
void printList(Node* head);

// Flip middle node
Node* flipMiddleNode(Node* head);
```

**Usage:**
```cpp
Node* list = buildList();           // Creates A -> B -> C -> D -> E
printList(list);                    // Displays list
list = flipMiddleNode(list);        // Flips to A -> C -> B -> D -> E
printList(list);                    // Display result
```

### OOP Class Approach
```cpp
SingleNodeFlipper flipper(values);
flipper.print();
flipper.flipMiddle();
```

---

## Part 2: Double Node Flip

### Free Functions
```cpp
DNode* buildDoublyList();
void printDoublyList(DNode* head);
DNode* flipMiddleDoublyNode(DNode* head);
```

**Usage:**
```cpp
DNode* dlist = buildDoublyList();    // Creates A ⇄ B ⇄ C ⇄ D ⇄ E
printDoublyList(dlist);
dlist = flipMiddleDoublyNode(dlist); // Flips to A ⇄ C ⇄ B ⇄ D ⇄ E
```

### OOP Class Approach
```cpp
DoubleNodeFlipper flipper(values);
flipper.print();
flipper.flipMiddle();
```

---

## Part 3: Tri-Node Rotations

### Free Functions
```cpp
TreeNode* buildTree();
void printTree(TreeNode* node, int indent = 0);
void rotateLeft(TreeNode* x, TreeNode*& root);
void rotateRight(TreeNode* y, TreeNode*& root);
```

**Usage:**
```cpp
TreeNode* root = buildTree();
printTree(root);

// Find node X (you'll need to traverse or store reference)
rotateLeft(nodeX, root);
printTree(root);

rotateRight(nodeY, root);
```

### OOP Class Approach
```cpp
TreeRotator rotator;
rotator.print();
TreeNode* x = rotator.findNode('X');
rotator.rotateLeft(x);
```

---

## Part 4: Quad Node Rotation

### Using Rotor Class
```cpp
Rotor rotor;
rotor.print();               // Show current state
int deg = rotor.rotateClockwise();  // Rotate 90°
```

### Using PrintRotor Function (Spec-Compliant)
```cpp
Rotor r;
PrintRotor(r);  // Demonstrates full 360° rotation
```

---

## Key Differences

| Aspect | Free Functions | OOP Classes |
|--------|---------------|-------------|
| **Matches Spec** | ✅ Exact signatures | Additional approach |
| **Encapsulation** | ❌ No state management | ✅ Encapsulated |
| **Memory** | Manual management | Destructors handle cleanup |
| **Reusability** | Works with raw pointers | Works with any data |
|**Testing** | Matches assignment examples | More flexible |

---

## Compilation

Both approaches are in the same `main.cpp` file:

```cmd
cd c:\Personals\assignment1
g++ -std=c++17 main.cpp -o node_assignment.exe
node_assignment.exe
```

---

## Which to Use?

**For Assignment Submission:**
- Use **free functions** if the grader expects exact function signatures
- The `buildList()`, `printList()`, etc. match the spec precisely

**For Learning OOP:**
- Use the **class approach** to demonstrate understanding of:
  - Constructors and destructors
  - Encapsulation
  - General-purpose design

**Safe Bet:**
- The current `main.cpp` demonstrates **BOTH** approaches
- Shows free functions first (spec-compliant)
- Then shows OOP approach for comparison
