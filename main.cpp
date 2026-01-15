/**
 * NODE MANIPULATION ASSIGNMENT
 * Four-part assignment implementing node pointer rewiring operations
 * All classes use proper OOP design with constructor-based initialization
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
 * SingleNodeFlipper class
 * Performs flip operation on middle node in singly linked list
 * 
 * Original:  A -> B -> C -> D -> E
 * Flipped:   A -> C -> B -> D -> E
 */
class SingleNodeFlipper {
private:
    Node* head;
    
public:
    // Constructor - builds list from vector of values
    SingleNodeFlipper(const std::vector<char>& values) {
        if (values.empty()) {
            head = nullptr;
            return;
        }
        
        head = new Node(values[0]);
        Node* current = head;
        
        for (size_t i = 1; i < values.size(); i++) {
            current->next = new Node(values[i]);
            current = current->next;
        }
    }
    
    // Find the middle node by counting nodes and dividing by 2
    Node* findMiddleNode() {
        if (!head) return nullptr;
        
        // Count total nodes
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        
        // Find middle index (integer division)
        int middleIndex = count / 2;
        
        // Navigate to middle node
        temp = head;
        for (int i = 0; i < middleIndex; i++) {
            temp = temp->next;
        }
        
        return temp;
    }
    
    // Flip the middle node with its previous node
    void flipMiddle() {
        if (!head || !head->next) return; // Need at least 2 nodes
        
        // Count nodes and find middle index
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        
        int middleIndex = count / 2;
        if (middleIndex == 0) return; // Can't flip if middle is head
        
        // Find the node before the one before middle (A if flipping B and C)
        Node* beforePrev = nullptr;
        Node* prev = head;
        Node* middle = head;
        
        // Navigate to positions
        for (int i = 0; i < middleIndex; i++) {
            beforePrev = prev;
            prev = middle;
            middle = middle->next;
        }
        
        if (!middle) return; // Safety check
        
        // Rewire pointers
        // Original: beforePrev -> prev -> middle -> middle->next
        // Target:   beforePrev -> middle -> prev -> middle->next
        
        prev->next = middle->next;      // B points to D
        middle->next = prev;             // C points to B
        
        if (beforePrev) {
            beforePrev->next = middle;   // A points to C
        } else {
            head = middle;               // If prev was head, update head
        }
    }
    
    // Get head pointer
    Node* getHead() const {
        return head;
    }
    
    // Print the list
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "null\n";
    }
    
    // Destructor - clean up memory
    ~SingleNodeFlipper() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

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
 * DoubleNodeFlipper class
 * Performs flip operation on middle node in doubly linked list
 * 
 * Original:  A ⇄ B ⇄ C ⇄ D ⇄ E
 * Flipped:   A ⇄ C ⇄ B ⇄ D ⇄ E
 */
class DoubleNodeFlipper {
private:
    DNode* head;
    
public:
    // Constructor - builds doubly linked list from vector of values
    DoubleNodeFlipper(const std::vector<char>& values) {
        if (values.empty()) {
            head = nullptr;
            return;
        }
        
        head = new DNode(values[0]);
        DNode* current = head;
        
        for (size_t i = 1; i < values.size(); i++) {
            DNode* newNode = new DNode(values[i]);
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
        }
    }
    
    // Find the middle node by counting nodes and dividing by 2
    DNode* findMiddleNode() {
        if (!head) return nullptr;
        
        // Count total nodes
        int count = 0;
        DNode* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        
        // Find middle index (integer division)
        int middleIndex = count / 2;
        
        // Navigate to middle node
        temp = head;
        for (int i = 0; i < middleIndex; i++) {
            temp = temp->next;
        }
        
        return temp;
    }
    
    // Flip the middle node with its previous node
    void flipMiddle() {
        if (!head || !head->next) return; // Need at least 2 nodes
        
        // Count nodes and find middle index
        int count = 0;
        DNode* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        
        int middleIndex = count / 2;
        if (middleIndex == 0) return; // Can't flip if middle is head
        
        // Find the relevant nodes
        DNode* beforePrev = nullptr;
        DNode* prev = head;
        DNode* middle = head;
        
        // Navigate to positions
        for (int i = 0; i < middleIndex; i++) {
            beforePrev = prev;
            prev = middle;
            middle = middle->next;
        }
        
        if (!middle) return; // Safety check
        
        DNode* afterMiddle = middle->next;
        
        // Rewire all bidirectional pointers
        // Original: beforePrev ⇄ prev ⇄ middle ⇄ afterMiddle
        // Target:   beforePrev ⇄ middle ⇄ prev ⇄ afterMiddle
        
        // Connect beforePrev to middle
        if (beforePrev) {
            beforePrev->next = middle;
            middle->prev = beforePrev;
        } else {
            head = middle;
            middle->prev = nullptr;
        }
        
        // Connect middle to prev
        middle->next = prev;
        prev->prev = middle;
        
        // Connect prev to afterMiddle
        prev->next = afterMiddle;
        if (afterMiddle) {
            afterMiddle->prev = prev;
        }
    }
    
    // Get head pointer
    DNode* getHead() const {
        return head;
    }
    
    // Print the doubly linked list
    void print() const {
        DNode* current = head;
        while (current) {
            std::cout << current->data << " ⇄ ";
            current = current->next;
        }
        std::cout << "null\n";
    }
    
    // Destructor - clean up memory
    ~DoubleNodeFlipper() {
        DNode* current = head;
        while (current) {
            DNode* next = current->next;
            delete current;
            current = next;
        }
    }
};

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
 * TreeRotator class
 * Performs left and right rotations on binary tree nodes
 * 
 * Left Rotation at X:
 *     P              P
 *     |              |
 *     X      =>      Y
 *    / \            / \
 *   A   Y          X   C
 *      / \        / \
 *     B   C      A   B
 */
class TreeRotator {
private:
    TreeNode* root;
    
public:
    // Constructor - builds tree structure
    TreeRotator() {
        // Build the initial tree structure as shown in assignment
        TreeNode* P = new TreeNode('P');
        TreeNode* X = new TreeNode('X');
        TreeNode* A = new TreeNode('A');
        TreeNode* Y = new TreeNode('Y');
        TreeNode* B = new TreeNode('B');
        TreeNode* C = new TreeNode('C');
        
        // Set up relationships
        P->left = X;       X->parent = P;
        X->left = A;       A->parent = X;
        X->right = Y;      Y->parent = X;
        Y->left = B;       B->parent = Y;
        Y->right = C;      C->parent = Y;
        
        root = P;
    }
    
    /**
     * Perform left rotation at given node
     * Node becomes left child of its right child
     */
    void rotateLeft(TreeNode* x) {
        if (!x || !x->right) return; // Need right child to rotate
        
        TreeNode* y = x->right;
        TreeNode* p = x->parent;
        TreeNode* b = y->left;
        
        // Rewire pointers for left rotation
        // y becomes the new subtree root
        y->parent = p;
        if (p) {
            if (p->left == x) {
                p->left = y;
            } else {
                p->right = y;
            }
        } else {
            root = y; // y becomes new root if x was root
        }
        
        // x becomes left child of y
        y->left = x;
        x->parent = y;
        
        // b (y's original left child) becomes x's right child
        x->right = b;
        if (b) {
            b->parent = x;
        }
    }
    
    /**
     * Perform right rotation at given node
     * Node becomes right child of its left child
     */
    void rotateRight(TreeNode* y) {
        if (!y || !y->left) return; // Need left child to rotate
        
        TreeNode* x = y->left;
        TreeNode* p = y->parent;
        TreeNode* b = x->right;
        
        // Rewire pointers for right rotation
        // x becomes the new subtree root
        x->parent = p;
        if (p) {
            if (p->left == y) {
                p->left = x;
            } else {
                p->right = x;
            }
        } else {
            root = x; // x becomes new root if y was root
        }
        
        // y becomes right child of x
        x->right = y;
        y->parent = x;
        
        // b (x's original right child) becomes y's left child
        y->left = b;
        if (b) {
            b->parent = y;
        }
    }
    
    // Get root pointer
    TreeNode* getRoot() const {
        return root;
    }
    
    // Get node by value (helper for testing)
    TreeNode* findNode(TreeNode* node, char value) const {
        if (!node) return nullptr;
        if (node->data == value) return node;
        
        TreeNode* found = findNode(node->left, value);
        if (found) return found;
        
        return findNode(node->right, value);
    }
    
    TreeNode* findNode(char value) const {
        return findNode(root, value);
    }
    
    // Print tree structure (rotated 90 degrees for readability)
    void print() const {
        printTree(root, 0);
    }
    
private:
    void printTree(TreeNode* node, int indent) const {
        if (!node) return;
        
        // Print right subtree first (top of display)
        printTree(node->right, indent + 4);
        
        // Print current node
        std::cout << std::string(indent, ' ') << node->data << "\n";
        
        // Print left subtree (bottom of display)
        printTree(node->left, indent + 4);
    }
    
public:
    // Destructor - clean up memory
    ~TreeRotator() {
        destroyTree(root);
    }
    
private:
    void destroyTree(TreeNode* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
};

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
    
    std::vector<char> singleList = {'A', 'B', 'C', 'D', 'E'};
    SingleNodeFlipper singleFlipper(singleList);
    
    std::cout << "Original list:\n";
    singleFlipper.print();
    
    Node* middleNode = singleFlipper.findMiddleNode();
    std::cout << "\nMiddle node found: " << middleNode->data << "\n\n";
    
    std::cout << "Performing flip...\n\n";
    singleFlipper.flipMiddle();
    
    std::cout << "After flip:\n";
    singleFlipper.print();
    
    std::cout << "\nExpected: A -> C -> B -> D -> E -> null\n";
    std::cout << "Note: C continues to point to D through B\n";
    
    // ========== PART 2: Double Node Flip ==========
    printSeparator();
    std::cout << "PART 2: DOUBLE NODE FLIP (Doubly Linked List)\n";
    printSeparator();
    
    std::vector<char> doubleList = {'A', 'B', 'C', 'D', 'E'};
    DoubleNodeFlipper doubleFlipper(doubleList);
    
    std::cout << "Original list:\n";
    doubleFlipper.print();
    
    DNode* middleDNode = doubleFlipper.findMiddleNode();
    std::cout << "\nMiddle node found: " << middleDNode->data << "\n\n";
    
    std::cout << "Performing flip...\n\n";
    doubleFlipper.flipMiddle();
    
    std::cout << "After flip:\n";
    doubleFlipper.print();
    
    std::cout << "\nExpected: A ⇄ C ⇄ B ⇄ D ⇄ E ⇄ null\n";
    std::cout << "Note: All bidirectional links are maintained\n";
    
    // ========== PART 3: Tri-Node Rotations ==========
    printSeparator();
    std::cout << "PART 3: TRI-NODE ROTATIONS (Binary Tree)\n";
    printSeparator();
    
    TreeRotator rotator;
    
    std::cout << "Original tree:\n";
    rotator.print();
    
    std::cout << "\nPerforming LEFT ROTATION at X...\n\n";
    TreeNode* nodeX = rotator.findNode('X');
    rotator.rotateLeft(nodeX);
    
    std::cout << "After left rotation:\n";
    rotator.print();
    
    std::cout << "\nPerforming RIGHT ROTATION at Y to restore...\n\n";
    TreeNode* nodeY = rotator.findNode('Y');
    rotator.rotateRight(nodeY);
    
    std::cout << "After right rotation (restored):\n";
    rotator.print();
    
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
    std::cout << "- Proper OOP design with classes and constructors\n";
    std::cout << "- Pointer rewiring only (no node reconstruction)\n";
    std::cout << "- General-purpose implementations\n";
    std::cout << "- Encapsulated logic within classes\n";
    printSeparator();
    
    return 0;
}
