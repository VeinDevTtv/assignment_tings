// author: Abdelkarim Ait Bourich
// date: 2026-03-06
// assignment: binary search tree (bst)
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>

using namespace std;

class Node {
private:
    int   value;
    Node* parent;
    Node* left;
    Node* right;

public:
    // constructor
    explicit Node(int val)
        : value(val), parent(nullptr), left(nullptr), right(nullptr) {}

    // getters
    int   getValue()  const { return value; }
    Node* getParent() const { return parent; }
    Node* getLeft()   const { return left; }
    Node* getRight()  const { return right; }

    // setters
    void setParent(Node* p) { parent = p; }
    void setLeft(Node* l)   { left   = l; }
    void setRight(Node* r)  { right  = r; }
};

class BST {
private:
    Node* root;

    // internal iterative comparison-based insertion
    Node* insert(Node* root, int value) {
        if (root == nullptr) {
            return new Node(value);
        }
        Node* current = root;
        while (true) {
            // go left
            if (value < current->getValue()) {
                if (current->getLeft() == nullptr) {
                    Node* newNode = new Node(value);
                    newNode->setParent(current);
                    current->setLeft(newNode);
                    return root;
                }
                current = current->getLeft();
            } 
            // go right
            else { 
                if (current->getRight() == nullptr) {
                    Node* newNode = new Node(value);
                    newNode->setParent(current);
                    current->setRight(newNode);
                    return root;
                }
                current = current->getRight();
            }
        }
    }

public:
    // constructor
    BST() : root(nullptr) {}

    // destructor
    ~BST() {
        clear();
    }

    // insert value into tree
    void insert(int value) {
        root = insert(root, value);
    }

    // iteratively clear and delete tree
    void clear() {
        if (!root) return;
        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node* curr = s.top();
            s.pop();
            
            // push children before deleting current node
            if (curr->getRight()) s.push(curr->getRight());
            if (curr->getLeft()) s.push(curr->getLeft());

            delete curr;
        }
        root = nullptr;
    }

    // iteratively display tree
    void display() {
        if (!root) {
            cout << "Empty BST\n";
            return;
        }

        struct PrintNode {
            Node* node;
            string prefix;
            string label;
        };

        stack<PrintNode> s;
        s.push({root, "", "Root"});

        while (!s.empty()) {
            PrintNode curr = s.top();
            s.pop();

            if (curr.label == "Root") {
                cout << "Root: " << curr.node->getValue() << "\n";
            } else {
                cout << curr.prefix << curr.label << ": " << curr.node->getValue()
                     << " (parent: " << curr.node->getParent()->getValue() << ")\n";
            }

            string childPrefix = (curr.label == "Root") ? "  " : curr.prefix + "  ";

            // push right child first so left child is popped first
            if (curr.node->getRight()) {
                s.push({curr.node->getRight(), childPrefix, "Right"});
            }
            if (curr.node->getLeft()) {
                s.push({curr.node->getLeft(), childPrefix, "Left"});
            }
        }
    }
};

int main() {
    // seed random generator
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "===========================================\n";
    cout << "        Binary Search Tree (BST)           \n";
    cout << "===========================================\n\n";

    // task 1: generate vector
    int numElements = 9 + rand() % 7;
    vector<int> unsortedVec;
    
    while (unsortedVec.size() < (size_t)numElements) {
        int val = rand() % 100;
        if (find(unsortedVec.begin(), unsortedVec.end(), val) == unsortedVec.end()) {
            unsortedVec.push_back(val);
        }
    }

    cout << "1. Original Unsorted Vector:\n[ ";
    for (int v : unsortedVec) cout << v << " ";
    cout << "]\n\n";

    // task 2: build bst
    BST bst;
    int midIndex = unsortedVec.size() / 2;
    int rootValue = unsortedVec[midIndex];

    cout << "2. Building BST from Unsorted Vector (Middle element " << rootValue << " chosen as Root)...\n";
    
    // begin insertions
    bst.insert(rootValue);
    
    // insert remaining values
    for (size_t i = 0; i < unsortedVec.size(); ++i) {
        if (i == (size_t)midIndex) continue;
        bst.insert(unsortedVec[i]);
    }

    // task 3: display tree
    cout << "\n3. Displaying Unsorted BST:\n";
    bst.display();
    cout << "\n--------------------------------------------------------------\n\n";

    // task 4: rebuild using sorted input
    cout << "4. Rebuilding the BST Using Sorted Input\n";
    
    // copy and sort vector
    vector<int> sortedVec = unsortedVec;
    sort(sortedVec.begin(), sortedVec.end());
    
    cout << "Sorted Vector:\n[ ";
    for (int v : sortedVec) cout << v << " ";
    cout << "]\n\n";

    // empty original tree
    cout << "Clearing original tree...\n";
    bst.clear();

    // new root is middle element of sorted vector
    midIndex = sortedVec.size() / 2;
    rootValue = sortedVec[midIndex];
    cout << "Rebuilding BST from Sorted Vector (Middle element " << rootValue << " chosen as Root)...\n";
    
    bst.insert(rootValue);
    for (size_t i = 0; i < sortedVec.size(); ++i) {
        if (i == (size_t)midIndex) continue;
        bst.insert(sortedVec[i]);
    }

    cout << "\nDisplaying Sorted BST:\n";
    bst.display();
    cout << "\n===========================================\n";

    return 0;
}

/*
task 5: compare the two trees

the tree built from the unsorted vector provides a much more balanced structure. because the inserted values are randomized, they tend to branch off in both directions, dividing more evenly across left and right paths rather than clustering on one side.

the tree built from the sorted vector has the deepest path possible. because the data is inserted in ascending order, skipping the previously inserted middle element, it forms extremely long chains.

insertion order determines the branching topology. natural randomness scatters placements, keeping branches shallower but wider. conversely, sorted insertion strips away varied branching opportunities. for the sorted tree, the first half of the elements strictly forms a chain that steps left once and then trails exclusively to the right, while the second half forms a chain going exclusively to the right. this creates an extremely skewed, unbalanced layout.

a typical doubly linked list relates nodes in a strictly linear format. adding a parent pointer transforms the relationship to a hierarchical topology. this clear two-way lineage makes debugging significantly simpler because you can trace exactly from whom a child was spawned and step back up the tree, easily verifying its correct descent direction.
*/
