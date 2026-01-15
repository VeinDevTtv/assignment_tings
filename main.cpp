/**
 * Author: Abdelkarim Ait Bourich
 * Date: 2026-01-15
 * Description: Node manipulation assignment implementing pointer rewiring operations.
 */

#include <iostream>
#include <vector>
#include <string>

// ============================================================
// PART 1: SINGLE NODE FLIP (Singly Linked List)
// ============================================================

/**
 * Node class for singly linked list
 */
class Node {
public:
    char data;
    Node* next;
    
    Node(char val) : data(val), next(nullptr) {}
};

/**
 * Build list as specified in assignment
 * Creates the example list: A -> B -> C -> D -> E
 */
Node* buildList() {
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    A->next = B;
    B->next = C;
    C->next = D;
    D->next = E;
    return A;
}

/**
 * Print list function as specified in assignment
 */
void printList(Node* head) {
    while (head) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "null\n";
}

/**
 * Flip middle node function
 * Finds middle node using integer math (count / 2) and flips it
 * Returns new head pointer (in case head changes)
 */
Node* flipMiddleNode(Node* head) {
    if (!head || !head->next) return head;
    
    // Count nodes
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    
    int middleIndex = count / 2;
    if (middleIndex == 0) return head;
    
    // Find nodes to flip
    Node* beforePrev = nullptr;
    Node* prev = head;
    Node* middle = head;
    
    for (int i = 0; i < middleIndex; i++) {
        beforePrev = prev;
        prev = middle;
        middle = middle->next;
    }
    
    if (!middle) return head;
    
    // Rewire pointers
    prev->next = middle->next;      // B points to D
    middle->next = prev;             // C points to B
    
    if (beforePrev) {
        beforePrev->next = middle;   // A points to C
        return head;
    } else {
        return middle;               // New head if prev was head
    }
}

// ============================================================
// PART 2: DOUBLE NODE FLIP (Doubly Linked List)
// ============================================================

/**
 * DNode class for doubly linked list
 */
class DNode {
public:
    char data;
    DNode* prev;
    DNode* next;
    
    DNode(char val) : data(val), prev(nullptr), next(nullptr) {}
};

/**
 * Build doubly linked list as specified in assignment
 */
DNode* buildDoublyList() {
    DNode* A = new DNode('A');
    DNode* B = new DNode('B');
    DNode* C = new DNode('C');
    DNode* D = new DNode('D');
    DNode* E = new DNode('E');
    A->next = B;
    B->prev = A; B->next = C;
    C->prev = B; C->next = D;
    D->prev = C; D->next = E;
    E->prev = D;
    return A;
}

/**
 * Print doubly linked list
 */
void printDoublyList(DNode* head) {
    while (head) {
        std::cout << head->data << " ⇄ ";
        head = head->next;
    }
    std::cout << "null\n";
}

/**
 * Flip middle node in doubly linked list
 */
DNode* flipMiddleDoublyNode(DNode* head) {
    if (!head || !head->next) return head;
    
    // Count nodes
    int count = 0;
    DNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    
    int middleIndex = count / 2;
    if (middleIndex == 0) return head;
    
    // Find nodes
    DNode* beforePrev = nullptr;
    DNode* prev = head;
    DNode* middle = head;
    
    for (int i = 0; i < middleIndex; i++) {
        beforePrev = prev;
        prev = middle;
        middle = middle->next;
    }
    
    if (!middle) return head;
    
    DNode* afterMiddle = middle->next;
    
    // Rewire bidirectional pointers
    if (beforePrev) {
        beforePrev->next = middle;
        middle->prev = beforePrev;
    } else {
        middle->prev = nullptr;
    }
    
    middle->next = prev;
    prev->prev = middle;
    
    prev->next = afterMiddle;
    if (afterMiddle) {
        afterMiddle->prev = prev;
    }
    
    return beforePrev ? head : middle;
}

// ============================================================
// PART 3: TRI-NODE ROTATIONS (Binary Tree)
// ============================================================

/**
 * TreeNode class for binary tree
 */
class TreeNode {
public:
    char data;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(char val) : data(val), parent(nullptr), left(nullptr), right(nullptr) {}
};

/**
 * Build tree as specified in assignment
 */
TreeNode* buildTree() {
    TreeNode* P = new TreeNode('P');
    TreeNode* X = new TreeNode('X');
    TreeNode* A = new TreeNode('A');
    TreeNode* Y = new TreeNode('Y');
    TreeNode* B = new TreeNode('B');
    TreeNode* C = new TreeNode('C');

    P->left = X;       X->parent = P;
    X->left = A;       A->parent = X;
    X->right = Y;      Y->parent = X;
    Y->left = B;       B->parent = Y;
    Y->right = C;      C->parent = Y;

    return P;
}

/**
 * Print tree helper
 */
void printTreeHelper(TreeNode* node, int indent) {
    if (!node) return;
    printTreeHelper(node->right, indent + 4);
    std::cout << std::string(indent, ' ') << node->data << "\n";
    printTreeHelper(node->left, indent + 4);
}

/**
 * Print tree function as specified in assignment
 */
void printTree(TreeNode* node, int indent = 0) {
    printTreeHelper(node, indent);
}

/**
 * Left rotation function
 */
void rotateLeft(TreeNode* x, TreeNode*& root) {
    if (!x || !x->right) return;
    
    TreeNode* y = x->right;
    TreeNode* p = x->parent;
    TreeNode* b = y->left;
    
    y->parent = p;
    if (p) {
        if (p->left == x) p->left = y;
        else p->right = y;
    } else {
        root = y;
    }
    
    y->left = x;
    x->parent = y;
    
    x->right = b;
    if (b) b->parent = x;
}

/**
 * Right rotation function
 */
void rotateRight(TreeNode* y, TreeNode*& root) {
    if (!y || !y->left) return;
    
    TreeNode* x = y->left;
    TreeNode* p = y->parent;
    TreeNode* b = x->right;
    
    x->parent = p;
    if (p) {
        if (p->left == y) p->left = x;
        else p->right = x;
    } else {
        root = x;
    }
    
    x->right = y;
    y->parent = x;
    
    y->left = b;
    if (b) b->parent = y;
}

/**
 * Helper function to find a node by value in the tree
 */
TreeNode* findNode(TreeNode* node, char value) {
    if (!node) return nullptr;
    if (node->data == value) return node;
    
    TreeNode* found = findNode(node->left, value);
    if (found) return found;
    
    return findNode(node->right, value);
}

// ============================================================
// PART 4: QUAD NODE ROTATION (4-Directional)
// ============================================================

/**
 * QuadNode class for 4-directional linked structure
 */
class QuadNode {
public:
    char data;
    QuadNode* north;
    QuadNode* east;
    QuadNode* south;
    QuadNode* west;
    
    QuadNode(char val) : data(val), north(nullptr), east(nullptr), 
                         south(nullptr), west(nullptr) {}
};

/**
 * Rotor class
 * Manages a QuadNode and performs 90-degree clockwise rotations
 * 
 * Initial (0°):     After 1st (90°):   After 2nd (180°):  After 3rd (270°):
 *     [A]               [D]                [C]                [B]
 *      ↑                 ↑                  ↑                   ↑
 * [D]← X →[B]       [C]← X →[A]        [B]← X →[D]        [A]← X →[C]
 *      ↓                 ↓                  ↓                   ↓
 *     [C]               [B]                [A]                [D]
 */
class Rotor {
private:
    int degrees;      // Current rotation: 0, 90, 180, or 270
    QuadNode* center; // The central node X
    QuadNode* nodeA;  // North node initially
    QuadNode* nodeB;  // East node initially
    QuadNode* nodeC;  // South node initially
    QuadNode* nodeD;  // West node initially
    
public:
    // Constructor - builds initial quad structure
    Rotor() : degrees(0) {
        // Create all nodes
        center = new QuadNode('X');
        nodeA = new QuadNode('A');
        nodeB = new QuadNode('B');
        nodeC = new QuadNode('C');
        nodeD = new QuadNode('D');
        
        // Set up initial configuration (0 degrees)
        center->north = nodeA;
        center->east = nodeB;
        center->south = nodeC;
        center->west = nodeD;
    }
    
    /**
     * Rotate clockwise by 90 degrees
     * Each direction shifts: north→east, east→south, south→west, west→north
     * Returns the current degree value after rotation
     */
    int rotateClockwise() {
        // Save current pointers
        QuadNode* tempNorth = center->north;
        QuadNode* tempEast = center->east;
        QuadNode* tempSouth = center->south;
        QuadNode* tempWest = center->west;
        
        // Rotate: each direction moves clockwise
        center->east = tempNorth;   // north → east
        center->south = tempEast;   // east → south
        center->west = tempSouth;   // south → west
        center->north = tempWest;   // west → north
        
        // Update rotation tracker
        degrees = (degrees + 90) % 360;
        
        return degrees;
    }
    
    // Get current rotation degrees
    int getDegrees() const {
        return degrees;
    }
    
    // Print current configuration
    void print() const {
        std::cout << "    [" << center->north->data << "]\n";
        std::cout << "     ↑\n";
        std::cout << "[" << center->west->data << "] ← " 
                  << center->data << " → [" << center->east->data << "]\n";
        std::cout << "     ↓\n";
        std::cout << "    [" << center->south->data << "]\n";
        std::cout << "Rotation: " << degrees << "°\n\n";
    }
    
    // Destructor - clean up memory
    ~Rotor() {
        delete center;
        delete nodeA;
        delete nodeB;
        delete nodeC;
        delete nodeD;
    }
};

/**
 * Print utility function as specified in assignment
 */
void PrintRotor(Rotor& r) {
    std::cout << "=== Rotor Full Rotation Test ===\n\n";
    std::cout << "Initial State:\n";
    r.print();
    
    for (int i = 0; i < 4; i++) {
        int degrees = r.rotateClockwise();
        std::cout << "After rotation to " << degrees << "°:\n";
        r.print();
    }
}

// ============================================================
// MAIN PROGRAM - Testing All Four Parts
// ============================================================

void printSeparator() {
    std::cout << "\n" << std::string(60, '=') << "\n\n";
}

int main() {
    std::cout << "NODE MANIPULATION ASSIGNMENT\n";
    std::cout << "Four Parts: Single, Double, Tree, and Quad Node Operations\n";
    
    // ========== PART 1: Single Node Flip ==========
    printSeparator();
    std::cout << "PART 1: SINGLE NODE FLIP (Singly Linked List)\n";
    printSeparator();
    
    Node* list1 = buildList();
    std::cout << "Original list:\n";
    printList(list1);
    
    std::cout << "\nPerforming flip...\n\n";
    list1 = flipMiddleNode(list1);
    
    std::cout << "After flip:\n";
    printList(list1);
    std::cout << "\nExpected: A -> C -> B -> D -> E -> null\n";
    std::cout << "Note: C continues to point to D through B\n";
    
    // ========== PART 2: Double Node Flip ==========
    printSeparator();
    std::cout << "PART 2: DOUBLE NODE FLIP (Doubly Linked List)\n";
    printSeparator();
    
    DNode* list2 = buildDoublyList();
    std::cout << "Original list:\n";
    printDoublyList(list2);
    
    std::cout << "\nPerforming flip...\n\n";
    list2 = flipMiddleDoublyNode(list2);
    
    std::cout << "After flip:\n";
    printDoublyList(list2);
    std::cout << "\nExpected: A ⇄ C ⇄ B ⇄ D ⇄ E ⇄ null\n";
    std::cout << "Note: All bidirectional links are maintained\n";
    
    // ========== PART 3: Tri-Node Rotations ==========
    printSeparator();
    std::cout << "PART 3: TRI-NODE ROTATIONS (Binary Tree)\n";
    printSeparator();
    
    TreeNode* root = buildTree();
    std::cout << "Original tree:\n";
    printTree(root);
    
    std::cout << "\nPerforming LEFT ROTATION at X...\n\n";
    TreeNode* nodeX = findNode(root, 'X');
    rotateLeft(nodeX, root);
    
    std::cout << "After left rotation:\n";
    printTree(root);
    
    std::cout << "\nPerforming RIGHT ROTATION at Y to restore...\n\n";
    TreeNode* nodeY = findNode(root, 'Y');
    rotateRight(nodeY, root);
    
    std::cout << "After right rotation (restored):\n";
    printTree(root);
    std::cout << "\nNote: Tree structure has been restored to original\n";
    
    // ========== PART 4: Quad Node Rotation ==========
    printSeparator();
    std::cout << "PART 4: QUAD NODE ROTATION (4-Directional)\n";
    printSeparator();
    
    Rotor rotor;
    PrintRotor(rotor);
    
    std::cout << "Note: After 4 rotations (360°), structure returns to original state\n";
    
    // ========== Summary ==========
    printSeparator();
    std::cout << "ASSIGNMENT COMPLETE\n";
    printSeparator();
    std::cout << "All four parts implemented using:\n";
    std::cout << "- Pointer rewiring only (no node reconstruction)\n";
    std::cout << "- Free functions matching assignment specification\n";
    std::cout << "- Rotor class for Part 4\n";
    printSeparator();
    
    return 0;
}
