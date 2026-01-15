/**
 * Author: Abdelkarim Ait Bourich
 * Date: 2026-01-15
 * Description: Node manipulation assignment implementing pointer rewiring operations.
 */

#include <iostream>
#include <vector>
#include <string>

// part 1: single node flip

// node for singly linked list
class Node {
public:
    char data;
    Node* next;
    
    Node(char val) : data(val), next(nullptr) {}
};

// build list a->b->c->d->e
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

// print the list
void printList(Node* head) {
    while (head) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "null\n";
}

// flip middle node by rewiring pointers
Node* flipMiddleNode(Node* head) {
    if (!head || !head->next) return head;
    
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    
    int middleIndex = count / 2;
    if (middleIndex == 0) return head;
    
    Node* beforePrev = nullptr;
    Node* prev = head;
    Node* middle = head;
    
    for (int i = 0; i < middleIndex; i++) {
        beforePrev = prev;
        prev = middle;
        middle = middle->next;
    }
    
    if (!middle) return head;
    
    prev->next = middle->next;
    middle->next = prev;
    
    if (beforePrev) {
        beforePrev->next = middle;
        return head;
    } else {
        return middle;
    }
}

// part 2: double node flip

// node for doubly linked list
class DNode {
public:
    char data;
    DNode* prev;
    DNode* next;
    
    DNode(char val) : data(val), prev(nullptr), next(nullptr) {}
};

// build doubly linked list a⇄b⇄c⇄d⇄e
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

// print doubly linked list
void printDoublyList(DNode* head) {
    while (head) {
        std::cout << head->data << " ⇄ ";
        head = head->next;
    }
    std::cout << "null\n";
}

// flip middle node maintaining bidirectional links
DNode* flipMiddleDoublyNode(DNode* head) {
    if (!head || !head->next) return head;
    
    int count = 0;
    DNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    
    int middleIndex = count / 2;
    if (middleIndex == 0) return head;
    
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

// part 3: tree rotations

// node for binary tree
class TreeNode {
public:
    char data;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(char val) : data(val), parent(nullptr), left(nullptr), right(nullptr) {}
};

// build tree structure
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

// helper for printing tree
void printTreeHelper(TreeNode* node, int indent) {
    if (!node) return;
    printTreeHelper(node->right, indent + 4);
    std::cout << std::string(indent, ' ') << node->data << "\n";
    printTreeHelper(node->left, indent + 4);
}

// print tree
void printTree(TreeNode* node, int indent = 0) {
    printTreeHelper(node, indent);
}

// rotate left
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

// rotate right
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

// find node by value
TreeNode* findNode(TreeNode* node, char value) {
    if (!node) return nullptr;
    if (node->data == value) return node;
    
    TreeNode* found = findNode(node->left, value);
    if (found) return found;
    
    return findNode(node->right, value);
}

// part 4: quad node rotation

// node with 4 directions
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

// rotor class manages quad node rotation
class Rotor {
private:
    int degrees;
    QuadNode* center;
    QuadNode* nodeA;
    QuadNode* nodeB;
    QuadNode* nodeC;
    QuadNode* nodeD;
    
public:
    Rotor() : degrees(0) {
        center = new QuadNode('X');
        nodeA = new QuadNode('A');
        nodeB = new QuadNode('B');
        nodeC = new QuadNode('C');
        nodeD = new QuadNode('D');
        
        center->north = nodeA;
        center->east = nodeB;
        center->south = nodeC;
        center->west = nodeD;
    }
    
    // rotate 90 degrees clockwise
    int rotateClockwise() {
        QuadNode* tempNorth = center->north;
        QuadNode* tempEast = center->east;
        QuadNode* tempSouth = center->south;
        QuadNode* tempWest = center->west;
        
        center->east = tempNorth;
        center->south = tempEast;
        center->west = tempSouth;
        center->north = tempWest;
        
        degrees = (degrees + 90) % 360;
        
        return degrees;
    }
    
    int getDegrees() const {
        return degrees;
    }
    
    void print() const {
        std::cout << "    [" << center->north->data << "]\n";
        std::cout << "     ↑\n";
        std::cout << "[" << center->west->data << "] ← " 
                  << center->data << " → [" << center->east->data << "]\n";
        std::cout << "     ↓\n";
        std::cout << "    [" << center->south->data << "]\n";
        std::cout << "Rotation: " << degrees << "°\n\n";
    }
    
    ~Rotor() {
        delete center;
        delete nodeA;
        delete nodeB;
        delete nodeC;
        delete nodeD;
    }
};

// demonstrate full rotation cycle
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

// main program

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
