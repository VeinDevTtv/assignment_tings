# Node Manipulation Assignment - README

## Author
Abdelkarim Ait Bourich  
Date: 2026-01-15

## Project Structure

```
assignment1/
└── main.cpp           # Single file containing all implementations
```

## Implementation Overview

This assignment implements four node manipulation operations using **pointer rewiring**:

### Part 1: Single Node Flip
- **Node class** - Basic singly linked list node
- **buildList()** - Creates A → B → C → D → E
- **printList(Node* head)** - Displays the list
- **flipMiddleNode(Node* head)** - Flips middle node

**Result:** A → C → B → D → E (C continues pointing to D through B)

### Part 2: Double Node Flip
- **DNode class** - Doubly linked list node
- **buildDoublyList()** - Creates A ⇄ B ⇄ C ⇄ D ⇄ E
- **printDoublyList(DNode* head)** - Displays the list
- **flipMiddleDoublyNode(DNode* head)** - Flips middle node maintaining bidirectional links

**Result:** A ⇄ C ⇄ B ⇄ D ⇄ E

### Part 3: Tri-Node Rotations
- **TreeNode class** - Binary tree node with parent pointer
- **buildTree()** - Creates tree structure
- **printTree(TreeNode* node, int indent)** - Visualizes tree
- **rotateLeft(TreeNode* x, TreeNode*& root)** - Left rotation
- **rotateRight(TreeNode* y, TreeNode*& root)** - Right rotation
- **findNode(TreeNode* node, char value)** - Helper to locate nodes

**Demonstrates:** Left rotation at X, then right rotation at Y to restore

### Part 4: Quad Node Rotation
- **QuadNode class** - 4-directional node
- **Rotor class** - Manages quad structure with rotation logic
- **rotateClockwise()** - Rotates 90° clockwise
- **PrintRotor(Rotor& r)** - Demonstrates full 360° cycle

**Demonstrates:** Four 90° rotations returning to original state

## Compilation

### Requirements
- C++11 or higher
- Standard library support

### Build Instructions

**Windows:**
```cmd
cd c:\Personals\assignment1
g++ -std=c++17 main.cpp -o node_assignment.exe
node_assignment.exe
```

**Linux/Mac:**
```bash
cd /path/to/assignment1
g++ -std=c++17 main.cpp -o node_assignment
./node_assignment
```

## Key Implementation Details

✅ **Pointer Rewiring Only** - No node reconstruction or value changes  
✅ **Spec-Compliant Functions** - All function signatures match assignment  
✅ **Integer Math for Middle** - Uses count / 2 to find middle nodes  
✅ **Memory Safety** - Proper null checks and boundary conditions

## Expected Output

The program displays:
1. **Part 1:** Single linked list before and after flip
2. **Part 2:** Doubly linked list before and after flip
3. **Part 3:** Tree structure showing left rotation, then restoration via right rotation
4. **Part 4:** Quad node through all four 90° rotations

Each section includes clear labels and expected results for verification.

## Design Philosophy

This implementation uses:
- **Free functions** for Parts 1-3 (matching assignment specification exactly)
- **Rotor class** for Part 4 (encapsulates quad rotation logic)
- **Direct pointer manipulation** for all transformations
- **No global variables** or hardcoded dependencies
