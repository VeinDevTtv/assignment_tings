# Node Manipulation Assignment - README

## Assignment Overview

This project implements four distinct node manipulation operations in C++ using proper object-oriented design. Each operation performs pointer rewiring to transform data structures without rebuilding nodes or changing values.

## Project Structure

```
assignment1/
└── main.cpp                  # Single file containing all classes and test driver
```

All four parts are implemented in a single source file for easy compilation and submission.

## Compilation

### Requirements
- C++17 compatible compiler (g++, clang++, MSVC)
- Standard library support

### Build Instructions

**Windows (using g++):**
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

## Implementation Details

### Part 1: Single Node Flip
Flips the middle node in a singly linked list by rewiring pointers:
- **Input:** A → B → C → D → E
- **Output:** A → C → B → D → E

### Part 2: Double Node Flip
Flips the middle node in a doubly linked list maintaining bidirectional links:
- **Input:** A ⇄ B ⇄ C ⇄ D ⇄ E
- **Output:** A ⇄ C ⇄ B ⇄ D ⇄ E

### Part 3: Tri-Node Rotations
Performs left and right rotations on binary tree nodes:
- Left rotation at X makes Y the new parent
- Right rotation at Y restores original structure

### Part 4: Quad Node Rotation
Rotates a 4-directional node 90° clockwise:
- Tracks rotation: 0°, 90°, 180°, 270°
- After 4 rotations, returns to original state

## Design Philosophy

✅ **Pointer Rewiring Only** - No node reconstruction or value changes  
✅ **Proper OOP Design** - All logic encapsulated in classes  
✅ **General-Purpose** - Works with any node configuration  
✅ **No Hardcoding** - Constructors accept parameters, no A/B/C/D/E dependencies

## Testing

Run the compiled program to see all four parts demonstrated with:
- Initial state visualization
- Operation execution
- Final state verification
- Expected output comparison

## Author Notes

This implementation follows the assignment's corrected specification:
- Uses class-based design with constructors
- Implements general-purpose algorithms
- Avoids hardcoded examples from the original problem statement
- Performs in-place pointer manipulation only
