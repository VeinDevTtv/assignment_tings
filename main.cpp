// Author: Abdelkarim Ait Bourich
// Date: 2026-02-05
// sorry i wasnt able to finish the assignment on time due to some personal issues
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// node class - stores value and pointers to smaller/larger nodes
class Node {
public:
    int value;
    Node* prev = nullptr;  // points to smaller value
    Node* next = nullptr;  // points to larger or equal value

    Node(int val) : value(val) {}
};

// ordered list class - manages nodes and all pointer operations
class OrderedList {
private:
    Node* center = nullptr;
    int nodeCount = 0;

    // deletes all nodes using bfs to handle both trees and lists
    void safeClear() {
        if (!center) return;

        vector<Node*> nodesToDelete;
        vector<Node*> q;
        
        q.push_back(center);
        nodesToDelete.push_back(center);

        size_t head = 0;
        while (head < q.size()) {
            Node* curr = q[head++];
            Node* neighbors[2] = {curr->prev, curr->next};
            for (Node* n : neighbors) {
                if (n && find(nodesToDelete.begin(), nodesToDelete.end(), n) == nodesToDelete.end()) {
                    nodesToDelete.push_back(n);
                    q.push_back(n);
                }
            }
        }

        for (Node* n : nodesToDelete) {
            delete n;
        }
    }

public:
    OrderedList() : center(nullptr), nodeCount(0) {}

    ~OrderedList() {
        safeClear();
    }

    // generates random vector of integers
    static vector<int> generateRandomVector(int size, int minVal, int maxVal) {
        vector<int> vec;
        for (int i = 0; i < size; i++) {
            vec.push_back(minVal + rand() % (maxVal - minVal + 1));
        }
        return vec;
    }

    // prints vector contents
    static void printVector(const vector<int>& vec, const string& label) {
        cout << label << ": [";
        for (size_t i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i < vec.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    // creates the center node
    void createCenter(int value) {
        center = new Node(value);
        nodeCount = 1;
    }

    Node* getCenter() const { return center; }
    int getNodeCount() const { return nodeCount; }

    // inserts node using local comparisons only (builds tree)
    void insertUnsorted(int value) {
        if (center == nullptr) {
            createCenter(value);
            return;
        }

        Node* current = center;

        while (true) {
            if (value < current->value) {
                if (current->prev == nullptr) {
                    Node* newNode = new Node(value);
                    current->prev = newNode;
                    nodeCount++;
                    return;
                }
                current = current->prev;
            } else {
                if (current->next == nullptr) {
                    Node* newNode = new Node(value);
                    current->next = newNode;
                    nodeCount++;
                    return;
                }
                current = current->next;
            }
        }
    }

    // inserts node maintaining global sorted order (builds list)
    void insertSorted(int value) {
        if (center == nullptr) {
            createCenter(value);
            return;
        }

        Node* current = center;

        while (true) {
            if (value < current->value) {
                if (current->prev == nullptr) {
                    Node* newNode = new Node(value);
                    newNode->next = current;
                    current->prev = newNode;
                    nodeCount++;
                    return;
                }
                if (value >= current->prev->value) {
                    Node* newNode = new Node(value);
                    Node* oldPrev = current->prev;
                    newNode->prev = oldPrev;
                    newNode->next = current;
                    oldPrev->next = newNode;
                    current->prev = newNode;
                    nodeCount++;
                    return;
                }
                current = current->prev;
            } else {
                if (current->next == nullptr) {
                    Node* newNode = new Node(value);
                    newNode->prev = current;
                    current->next = newNode;
                    nodeCount++;
                    return;
                }
                if (value < current->next->value) {
                    Node* newNode = new Node(value);
                    Node* oldNext = current->next;
                    newNode->prev = current;
                    newNode->next = oldNext;
                    oldNext->prev = newNode;
                    current->next = newNode;
                    nodeCount++;
                    return;
                }
                current = current->next;
            }
        }
    }

    // prints tree structure recursively
    void printLayer(Node* node, string prefix = "", bool isLast = true, string label = "Root") {
        if (!node) return;
        cout << prefix << (isLast ? "+-- " : "|-- ");
        cout << (label == "Center" ? "Center: " : label == "Prev" ? "<-- " : "--> ");
        cout << node->value << endl;

        prefix += isLast ? "    " : "|   ";
        bool hasPrev = node->prev != nullptr;
        bool hasNext = node->next != nullptr;
        if (hasPrev) printLayer(node->prev, prefix, !hasNext, "Prev");
        if (hasNext) printLayer(node->next, prefix, true, "Next");
    }

    // prints structure from center
    void print() {
        if (center == nullptr) {
            cout << "Empty OrderedList" << endl;
            return;
        }
        printLayer(center, "", true, "Center");
    }

    // clears all nodes
    void clear() {
        safeClear();
        center = nullptr;
        nodeCount = 0;
    }
};

// main program
// phase 1: build from unsorted vector (tree structure)
// phase 2: build from sorted vector (list structure)
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "===========================================" << endl;
    cout << "        Ordered List - Doubly Linked       " << endl;
    cout << "===========================================" << endl;
    cout << endl;

    // part 1: unsorted build
    cout << "-------------------------------------------" << endl;
    cout << "PART 1: Unsorted Build (Local Comparison)" << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;

    vector<int> randomVec = OrderedList::generateRandomVector(10, 0, 99);
    OrderedList::printVector(randomVec, "Generated Random Vector");
    cout << endl;

    OrderedList unsortedList;
    int centerValue = randomVec[5];
    cout << "Center value (index 5): " << centerValue << endl;
    unsortedList.createCenter(centerValue);
    cout << endl;

    cout << "Inserting remaining values:" << endl;
    for (int i = 0; i < 10; i++) {
        if (i != 5) {
            cout << "  Inserting: " << randomVec[i] << endl;
            unsortedList.insertUnsorted(randomVec[i]);
        }
    }
    cout << endl;

    cout << "UNSORTED ORDERED LIST STRUCTURE:" << endl;
    cout << "--------------------------------" << endl;
    unsortedList.print();
    cout << endl;
    cout << "Total nodes: " << unsortedList.getNodeCount() << endl;
    cout << endl;

    // part 2: sorted build
    cout << "-------------------------------------------" << endl;
    cout << "PART 2: Sorted Build (Global Order)" << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;

    vector<int> sortedVec = randomVec;
    sort(sortedVec.begin(), sortedVec.end());
    OrderedList::printVector(randomVec, "Original Vector");
    OrderedList::printVector(sortedVec, "Sorted Vector");
    cout << endl;

    OrderedList sortedList;
    int sortedCenterValue = sortedVec[5];
    cout << "Center value (index 5 of sorted): " << sortedCenterValue << endl;
    sortedList.createCenter(sortedCenterValue);
    cout << endl;

    cout << "Inserting remaining values (maintaining sorted order):" << endl;
    for (int i = 0; i < 10; i++) {
        if (i != 5) {
            cout << "  Inserting: " << sortedVec[i] << endl;
            sortedList.insertSorted(sortedVec[i]);
        }
    }
    cout << endl;

    cout << "SORTED ORDERED LIST STRUCTURE:" << endl;
    cout << "------------------------------" << endl;
    sortedList.print();
    cout << endl;
    cout << "Total nodes: " << sortedList.getNodeCount() << endl;
    cout << endl;

    // technical comparison
    cout << "-------------------------------------------" << endl;
    cout << "TECHNICAL COMPARISON" << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
    cout << "The unsorted build creates an irregular tree where node placement" << endl;
    cout << "depends on insertion order, often skewing deeper on one side." << endl;
    cout << "The sorted build produces linear chains: smaller values extend" << endl;
    cout << "only on prev, larger only on next, creating a balanced structure." << endl;
    cout << endl;

    return 0;
}
