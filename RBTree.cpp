#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#define RED     true
#define BLACK   false

#define COLOR_YELLOW "\033[93m"
#define COLOR_GREEN  "\033[92m"
#define COLOR_RED    "\033[91m"
#define COLOR_BLUE    "\033[96m"
#define COLOR_GRAY   "\033[90m"
#define COLOR_RESET  "\033[0m"

using namespace std;

struct Node {
    int data;
    bool color = RED;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(int val) : data(val) {}
};

class RedBlackTree {
public:
    void set_quiet(bool q) { quiet_ = q; }
    void reset_stats() {
        rotations_ = 0;
        recolors_ = 0;
        max_height_ = 0;
        height_history_.clear();
    }
    int get_rotations() const { return rotations_; }
    int get_recolors() const { return recolors_; }
    int get_final_height() const { return get_tree_height(root); }
    int get_max_height() const { return max_height_; }
    const vector<int>& get_height_history() const { return height_history_; }

    void insert(int value) {
        Node* newNode = new Node(value);
        root = bst_insert(root, newNode);
        fix_violation(newNode);
        int h = get_tree_height(root);
        if (h > max_height_) max_height_ = h;
        height_history_.push_back(h);
        if (!quiet_) print_bfs("After Insert " + to_string(value));
    }

private:
    Node* root = nullptr;
    bool quiet_ = false;
    int rotations_ = 0;
    int recolors_ = 0;
    int max_height_ = 0;
    vector<int> height_history_;

    void set_color(Node* node, bool color) {
        if (!node) return;
        if (node->color != color) {
            node->color = color;
            recolors_++;
        }
    }

    int get_tree_height(Node* n) const {
        return n ? 1 + max(get_tree_height(n->left), get_tree_height(n->right)) : 0;
    }

    Node* bst_insert(Node* curr, Node* node) {
        if (!curr) return node;

        if (node->data < curr->data) {
            curr->left = bst_insert(curr->left, node);
            curr->left->parent = curr;
        }
        else {
            curr->right = bst_insert(curr->right, node);
            curr->right->parent = curr;
        }
        return curr;
    }

    void rotate_left(Node* x) {
        rotations_++;
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;

        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;

        if (!quiet_) {
            cout << COLOR_GRAY << "\nRotation: Left around node " << x->data << COLOR_RESET << "\n";
            print_bfs("After Left Rotation");
        }
    }

    void rotate_right(Node* x) {
        rotations_++;
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;

        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->right = x;
        x->parent = y;

        if (!quiet_) {
            cout << COLOR_GRAY << "\nRotation: Right around node " << x->data << COLOR_RESET << "\n";
            print_bfs("After Right Rotation");
        }
    }

    void fix_violation(Node* node) {
        while (node != root && node->parent->color == RED) {
            Node* gp = node->parent->parent;

            if (node->parent == gp->left) {
                Node* uncle = gp->right;
                if (uncle && uncle->color == RED) {
                    set_color(node->parent, BLACK);
                    set_color(uncle, BLACK);
                    set_color(gp, RED);
                    node = gp;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotate_left(node);
                    }
                    set_color(node->parent, BLACK);
                    set_color(gp, RED);
                    rotate_right(gp);
                }
            }
            else {
                Node* uncle = gp->left;
                if (uncle && uncle->color == RED) {
                    set_color(node->parent, BLACK);
                    set_color(uncle, BLACK);
                    set_color(gp, RED);
                    node = gp;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotate_right(node);
                    }
                    set_color(node->parent, BLACK);
                    set_color(gp, RED);
                    rotate_left(gp);
                }
            }
        }
        set_color(root, BLACK);
    }

    void print_bfs(const string& label) {
        if (!root || quiet_) return;
        cout << COLOR_GRAY << "\nTree State: " << label << COLOR_RESET << "\n";

        queue<Node*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            bool hasNonNull = false;

            cout << "Level " << level << ":  ";
            for (int i = 0; i < size; ++i) {
                Node* node = q.front(); q.pop();

                if (node) {
                    string branch = (node == root) ? COLOR_YELLOW :
                        (node == node->parent->left) ? COLOR_GREEN :
                        COLOR_RED;

                    cout << branch << node->data << COLOR_RESET << "  ";
                    q.push(node->left);
                    q.push(node->right);
                    hasNonNull = true;
                }
                else {
                    cout << COLOR_GRAY << "-" << COLOR_RESET << "  ";
                    q.push(nullptr); // maintain structure
                    q.push(nullptr);
                }
            }
            cout << "\n";
            level++;

            // stop when next level has only nulls
            queue<Node*> temp = q;
            hasNonNull = false;
            while (!temp.empty()) {
                if (temp.front()) {
                    hasNonNull = true;
                    break;
                }
                temp.pop();
            }
            if (!hasNonNull) break;
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
    RedBlackTree tree;
    if (argc >= 2) {
        vector<int> data = parse_dataset(argv[1]);
        tree.set_quiet(true);
        tree.reset_stats();
        for (int val : data) tree.insert(val);
        cout << "rotations " << tree.get_rotations() << "\n";
        cout << "recolors " << tree.get_recolors() << "\n";
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
    vector<int> values = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
    for (int val : values) tree.insert(val);
    return 0;
}






