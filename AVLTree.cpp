#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#define COLOR_YELLOW "\033[33m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_RED    "\033[31m"
#define COLOR_CYAN   "\033[96m"
#define COLOR_GRAY   "\033[90m"
#define COLOR_RESET  "\033[0m"

struct Node {
    int data;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(int val) : data(val) {}
};

class AVLTree {
public:
    void set_quiet(bool q) { quiet_ = q; }
    void reset_stats() {
        rotations_ = 0;
        balance_checks_ = 0;
        max_height_ = 0;
        height_history_.clear();
    }
    int get_rotations() const { return rotations_; }
    int get_balance_checks() const { return balance_checks_; }
    int get_final_height() const { return root ? get_height(root) : 0; }
    int get_max_height() const { return max_height_; }
    const vector<int>& get_height_history() const { return height_history_; }

    void insert(int val) {
        root = insert_iterative(val);
        int h = get_final_height();
        if (h > max_height_) max_height_ = h;
        height_history_.push_back(h);
        if (!quiet_) print_bfs("After Insert " + to_string(val));
    }

private:
    Node* root = nullptr;
    bool quiet_ = false;
    int rotations_ = 0;
    int balance_checks_ = 0;
    int max_height_ = 0;
    vector<int> height_history_;

    int get_height(Node* node) const {
        return node ? node->height : 0;
    }

    int get_balance(Node* node) const {
        return node ? get_height(node->left) - get_height(node->right) : 0;
    }

    void update_height(Node* node) {
        node->height = 1 + max(get_height(node->left), get_height(node->right));
    }

    // reconnect rotated subtree to parent
    void reconnect_parent(Node* oldRoot, Node* newRoot) {
        Node* p = newRoot->parent;
        if (!p) {
            root = newRoot;
            return;
        }
        if (p->left == oldRoot)
            p->left = newRoot;
        else if (p->right == oldRoot)
            p->right = newRoot;
    }

    // iterative avl insertion
    Node* insert_iterative(int val) {
        if (!root) {
            root = new Node(val);
            return root;
        }

        Node* curr = root;
        Node* parent = nullptr;

        // iterative descent
        while (curr) {
            parent = curr;
            if (val < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        // insert new node
        Node* newNode = new Node(val);
        newNode->parent = parent;

        if (val < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        // walk upward and rebalance
        Node* node = parent;

        while (node) {
            update_height(node);
            int bf = get_balance(node);
            balance_checks_++;

            // left heavy
            if (bf > 1) {
                if (val < node->left->data) {
                    if (!quiet_) cout << COLOR_CYAN << "\nRotation: Right around node "
                        << node->data << COLOR_RESET << "\n";

                    Node* old = node;
                    node = rotate_right(node);
                    reconnect_parent(old, node);
                }
                else {
                    if (!quiet_) cout << COLOR_CYAN << "\nRotation: Left-Right around node "
                        << node->data << COLOR_RESET << "\n";

                    Node* L = node->left;
                    Node* oldL = L;
                    node->left = rotate_left(L);
                    node->left->parent = node;
                    reconnect_parent(oldL, node->left);

                    Node* old = node;
                    node = rotate_right(node);
                    reconnect_parent(old, node);
                }
            }

            // right heavy
            else if (bf < -1) {
                if (val >= node->right->data) {
                    if (!quiet_) cout << COLOR_CYAN << "\nRotation: Left around node "
                        << node->data << COLOR_RESET << "\n";

                    Node* old = node;
                    node = rotate_left(node);
                    reconnect_parent(old, node);
                }
                else {
                    if (!quiet_) cout << COLOR_CYAN << "\nRotation: Right-Left around node "
                        << node->data << COLOR_RESET << "\n";

                    Node* R = node->right;
                    Node* oldR = R;
                    node->right = rotate_right(R);
                    node->right->parent = node;
                    reconnect_parent(oldR, node->right);

                    Node* old = node;
                    node = rotate_left(node);
                    reconnect_parent(old, node);
                }
            }

            // if this node becomes root
            if (!node->parent)
                root = node;

            node = node->parent;
        }

        return root;
    }

    // rotations
    Node* rotate_left(Node* x) {
        rotations_++;
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;

        y->left = x;
        y->parent = x->parent;
        x->parent = y;

        update_height(x);
        update_height(y);

        return y;
    }

    Node* rotate_right(Node* x) {
        rotations_++;
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;

        y->right = x;
        y->parent = x->parent;
        x->parent = y;

        update_height(x);
        update_height(y);

        return y;
    }

    // bfs print
    void print_bfs(const string& label) {
        if (!root || quiet_) return;

        cout << COLOR_GRAY << "\nTree State: " << label << COLOR_RESET << "\n";
        queue<Node*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            cout << "Level " << level << ":  ";

            for (int i = 0; i < size; ++i) {
                Node* node = q.front(); q.pop();

                if (node) {
                    string color = (node == root) ? COLOR_YELLOW :
                        (node == node->parent->left) ? COLOR_GREEN : COLOR_RED;

                    cout << color << node->data << COLOR_RESET << "  ";
                    q.push(node->left);
                    q.push(node->right);
                }
                else {
                    cout << COLOR_GRAY << "-" << COLOR_RESET << "  ";
                    q.push(nullptr);
                    q.push(nullptr);
                }
            }

            cout << "\n";
            level++;

            bool hasRealNode = false;
            queue<Node*> temp = q;
            while (!temp.empty()) {
                if (temp.front()) {
                    hasRealNode = true;
                    break;
                }
                temp.pop();
            }
            if (!hasRealNode) break;
        }
    }
};

vector<int> parse_dataset(const string& path) {
    ifstream f(path);
    if (!f) return {};
    stringstream buf;
    buf << f.rdbuf();
    string s = buf.str();
    s.erase(remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(remove(s.begin(), s.end(), '\r'), s.end());
    size_t start = s.find('[');
    size_t end = s.rfind(']');
    if (start == string::npos || end == string::npos || start >= end) return {};
    s = s.substr(start + 1, end - start - 1);
    vector<int> out;
    stringstream ss(s);
    string token;
    while (getline(ss, token, ',')) {
        size_t i = token.find_first_not_of(" \t");
        if (i != string::npos) token = token.substr(i);
        if (token.empty()) continue;
        out.push_back(stoi(token));
    }
    return out;
}

int main(int argc, char* argv[]) {
    AVLTree tree;
    if (argc >= 2) {
        vector<int> data = parse_dataset(argv[1]);
        tree.set_quiet(true);
        tree.reset_stats();
        for (int val : data) tree.insert(val);
        cout << "rotations " << tree.get_rotations() << "\n";
        cout << "balance_checks " << tree.get_balance_checks() << "\n";
        cout << "final_height " << tree.get_final_height() << "\n";
        cout << "max_height " << tree.get_max_height() << "\n";
        cout << "height_history ";
        const vector<int>& history = tree.get_height_history();
        for (size_t i = 0; i < history.size(); ++i) {
            if (i) cout << ",";
            cout << history[i];
        }
        cout << "\n";
        return 0;
    }
    vector<int> input = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
    for (int val : input) tree.insert(val);
    return 0;
}




