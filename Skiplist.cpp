#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

// ansi color codes for output
const string reset   = "\033[0m";
const string red     = "\033[91m";
const string green   = "\033[92m";
const string yellow  = "\033[93m";
const string blue    = "\033[94m";
const string purple  = "\033[38;5;141m";
const string cyan    = "\033[96m";
const string white   = "\033[97m";
const string darkgray = "\033[38;5;250m";
const string orange  = "\033[38;5;208m";

// node with four directional pointers forming a 2d grid
class GridNode {
public:
    int key;
    int value;

    GridNode* left;
    GridNode* right;
    GridNode* up;
    GridNode* down;

    GridNode(int k, int v)
        : key(k), value(v),
          left(nullptr), right(nullptr),
          up(nullptr), down(nullptr) {}
};

// represents one horizontal level in the skip list
class Level {
    GridNode* head;   // first node in this level
    Level* down;      // next lower level

public:
    Level(GridNode* h = nullptr, Level* d = nullptr)
        : head(h), down(d) {}

    // accessors
    GridNode* getHead() const { return head; }
    void      setHead(GridNode* h) { head = h; }

    Level*    getDown() const { return down; }
    void      setDown(Level* d) { down = d; }
};

// skip list built entirely from linked gridnodes and levels
class SkipList {
    Level*  topLevel;       // highest level in the skip list
    double  probability;    // probability used for random height
    int     maxHeight;      // maximum allowed height

public:
    SkipList(double p = 0.5, int maxH = 16);
    ~SkipList();

    // core operations
    void      insert(int key, int value);
    GridNode* search(int key) const;

    // visualization
    void printLevels() const;

private:
    // helpers
    int       randomHeight()  const;
    int       countLevels()   const;
    Level*    ensureHeight(int height);
    GridNode* insertIntoLevel(Level* level, int key, int value);
    void      insertAtLevel(Level* level, GridNode* newNode, GridNode* belowNode);
    Level*    getLevelAt(int index) const;
};

// creates a single empty bottom level
SkipList::SkipList(double p, int maxH)
    : probability(p), maxHeight(maxH)
{
    topLevel = new Level();
}

// frees every level and every gridnode
SkipList::~SkipList() {
    Level* lvl = topLevel;
    while (lvl) {
        GridNode* node = lvl->getHead();
        while (node) {
            GridNode* next = node->right;
            delete node;
            node = next;
        }
        Level* below = lvl->getDown();
        delete lvl;
        lvl = below;
    }
}

// coin-flip height generator
int SkipList::randomHeight() const {
    int height = 1;
    while ((rand() / double(RAND_MAX)) < probability && height < maxHeight)
        height++;
    return height;
}

// returns the number of levels
int SkipList::countLevels() const {
    int count = 0;
    Level* lvl = topLevel;
    while (lvl) {
        count++;
        lvl = lvl->getDown();
    }
    return count;
}

// returns the level at index (0 = bottom)
Level* SkipList::getLevelAt(int index) const {
    int total = countLevels();
    int fromTop = total - 1 - index;
    Level* lvl = topLevel;
    for (int i = 0; i < fromTop && lvl; i++)
        lvl = lvl->getDown();
    return lvl;
}

// ensure the skip list has at least 'height' levels
Level* SkipList::ensureHeight(int height) {
    int current = countLevels();
    while (current < height) {
        Level* newLevel = new Level(nullptr, topLevel);
        topLevel = newLevel;
        current++;
    }
    return topLevel;
}

// insert a new node into a level's sorted horizontal doubly linked list
GridNode* SkipList::insertIntoLevel(Level* level, int key, int value) {
    GridNode* newNode = new GridNode(key, value);
    GridNode* head = level->getHead();

    // empty level or new node goes before head
    if (!head || key < head->key) {
        newNode->right = head;
        if (head)
            head->left = newNode;
        level->setHead(newNode);
        return newNode;
    }

    // walk right to find sorted position
    GridNode* prev = head;
    while (prev->right && prev->right->key < key)
        prev = prev->right;

    // wire: prev <-> newNode <-> next
    GridNode* next = prev->right;
    prev->right   = newNode;
    newNode->left  = prev;
    newNode->right = next;
    if (next)
        next->left = newNode;

    return newNode;
}

// insert a pre-built tower node into a level using left/up traversal
// from the node directly below — no re-searching from head
void SkipList::insertAtLevel(Level* level, GridNode* newNode, GridNode* belowNode) {
    // walk left from the node below to find a neighbor with an up pointer
    GridNode* cursor = belowNode->left;
    while (cursor && !cursor->up)
        cursor = cursor->left;

    if (cursor && cursor->up) {
        // found a left neighbor with an up link — insert after it
        GridNode* ref = cursor->up;
        // walk right from ref to find exact sorted position at this level
        while (ref->right && ref->right->key < newNode->key)
            ref = ref->right;

        // wire: ref <-> newNode <-> next
        GridNode* next = ref->right;
        ref->right     = newNode;
        newNode->left   = ref;
        newNode->right  = next;
        if (next)
            next->left = newNode;
    } else {
        // no left neighbor has an up link — insert at the front of this level
        GridNode* head = level->getHead();
        if (!head || newNode->key < head->key) {
            newNode->right = head;
            if (head)
                head->left = newNode;
            level->setHead(newNode);
        } else {
            // walk right from head to find position
            GridNode* prev = head;
            while (prev->right && prev->right->key < newNode->key)
                prev = prev->right;

            GridNode* next = prev->right;
            prev->right    = newNode;
            newNode->left   = prev;
            newNode->right  = next;
            if (next)
                next->left = newNode;
        }
    }
}

// full insertion: generate height, ensure levels, build tower, insert
void SkipList::insert(int key, int value) {
    cout << purple << "\n<<< Inserting key >>> "
         << yellow << key << reset << "\n";

    // step 1: random height for the new tower
    int height = randomHeight();

    // step 2: ensure enough levels exist
    ensureHeight(height);

    // step 3 (milestone 1): insert base node into level 0
    Level* baseLevel = getLevelAt(0);
    GridNode* below = insertIntoLevel(baseLevel, key, value);

    cout << green << "Inserted key " << yellow << key
         << green << " at level " << yellow << 0 << reset << "\n";

    // step 4 (milestones 2 & 3): build the tower upward, inserting
    // each new node horizontally and linking it vertically
    for (int i = 1; i < height; i++) {
        Level* lvl = getLevelAt(i);

        // create the upper tower node and link vertically (milestone 2)
        GridNode* upperNode = new GridNode(key, value);
        upperNode->down = below;
        below->up       = upperNode;

        // insert horizontally using left/up traversal (milestone 3)
        insertAtLevel(lvl, upperNode, below);

        cout << green << "Inserted key " << yellow << key
             << green << " at level " << yellow << i << reset << "\n";

        below = upperNode;
    }
}

// classic skip-list search using only right and down (milestone 4)
GridNode* SkipList::search(int key) const {
    cout << purple << "\n>>> Search <<< "
         << yellow << key << reset << "\n";

    // start at the topmost level's head node
    Level* lvl = topLevel;
    GridNode* node = nullptr;

    while (lvl) {
        node = lvl->getHead();

        if (!node || node->key > key) {
            // empty level or head overshoots — drop down one level
            lvl = lvl->getDown();
            continue;
        }

        // we have a valid starting node at this level — begin GridNode traversal
        // from here, use only right and down pointers
        while (node) {
            // move right while the next node's key <= target
            while (node->right && node->right->key <= key)
                node = node->right;

            // check if current node matches
            if (node->key == key) {
                cout << green << "Found key: " << yellow << key << reset << "\n";
                return node;
            }

            // drop down one level via the GridNode's down pointer
            if (node->down) {
                node = node->down;
            } else {
                // reached level 0, key not present
                cout << red << "Key not found" << reset << "\n";
                return nullptr;
            }
        }
    }

    cout << red << "Key not found" << reset << "\n";
    return nullptr;
}

// print the skip list level by level
void SkipList::printLevels() const {
    int total = countLevels();
    cout << orange << ">>> Skip List <<<" << reset << "\n";

    for (int i = total - 1; i >= 0; i--) {
        Level* lvl = getLevelAt(i);
        cout << green << "Level " << i << ": " << reset;

        GridNode* node = lvl->getHead();
        bool first = true;
        while (node) {
            if (!first)
                cout << darkgray << " -> " << reset;
            cout << yellow << node->key << reset;
            first = false;
            node = node->right;
        }

        if (first)
            cout << darkgray << "(empty)" << reset;

        cout << "\n";
    }
}

// demo: insert random keys, print structure, search
int main() {
    srand((unsigned)time(nullptr));

    const int N = 10;
    int ilist[N];
    for (int i = 0; i < N; i++)
        ilist[i] = rand() % 100 + 1;

    int nlevels = 4;
    SkipList skiplist(0.5, nlevels);

    for (int i = 0; i < N; i++) {
        skiplist.insert(ilist[i], ilist[i]);
        skiplist.printLevels();
    }

    cout << "\n";
    skiplist.printLevels();

    // search for a key that was inserted
    cout << "\n";
    skiplist.search(ilist[4]);

    // search for a key unlikely to exist
    cout << "\n";
    skiplist.search(999);

    return 0;
}