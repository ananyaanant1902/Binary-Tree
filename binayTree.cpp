#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    explicit Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(root); }

    // Insert by level order (fills the tree left-to-right, top-to-bottom)
    void insert(int value) {
        Node* n = new Node(value);
        if (!root) { root = n; return; }

        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            if (!cur->left) { cur->left = n; return; }
            if (!cur->right) { cur->right = n; return; }
            q.push(cur->left);
            q.push(cur->right);
        }
    }

    // Traversals
    vector<int> preorder()  const { vector<int> out; preorder(root, out);  return out; }
    vector<int> inorder()   const { vector<int> out; inorder(root, out);   return out; }
    vector<int> postorder() const { vector<int> out; postorder(root, out); return out; }
    vector<int> levelorder() const {
        vector<int> out;
        if (!root) return out;
        queue<Node*> q; q.push(root);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            out.push_back(cur->val);
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        return out;
    }

    // Utilities
    bool find(int target) const {
        if (!root) return false;
        queue<Node*> q; q.push(root);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            if (cur->val == target) return true;
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        return false;
    }

    int height() const { return height(root); }          // edges-based height (-1 for empty)
    int size()   const { return count(root); }

    bool isComplete() const {
        if (!root) return true;
        queue<Node*> q; q.push(root);
        bool seenNull = false;
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            if (cur->left) {
                if (seenNull) return false;
                q.push(cur->left);
            } else {
                seenNull = true;
            }
            if (cur->right) {
                if (seenNull) return false;
                q.push(cur->right);
            } else {
                seenNull = true;
            }
        }
        return true;
    }

private:
    Node* root;

    static void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    static void preorder(Node* n, vector<int>& out) {
        if (!n) return;
        out.push_back(n->val);
        preorder(n->left, out);
        preorder(n->right, out);
    }
    static void inorder(Node* n, vector<int>& out) {
        if (!n) return;
        inorder(n->left, out);
        out.push_back(n->val);
        inorder(n->right, out);
    }
    static void postorder(Node* n, vector<int>& out) {
        if (!n) return;
        postorder(n->left, out);
        postorder(n->right, out);
        out.push_back(n->val);
    }
    static int height(Node* n) {
        if (!n) return -1; // empty tree has height -1, leaf has 0
        return 1 + max(height(n->left), height(n->right));
    }
    static int count(Node* n) {
        if (!n) return 0;
        return 1 + count(n->left) + count(n->right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BinaryTree bt;
    // Demo: build a small tree
    for (int x : {10, 20, 30, 40, 50, 60}) bt.insert(x);

    auto print = [](const string& name, const vector<int>& v) {
        cout << name << ": ";
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i] << (i + 1 < v.size() ? ' ' : '\n');
        }
    };

    print("Preorder", bt.preorder());     // 10 20 40 50 30 60
    print("Inorder", bt.inorder());       // 40 20 50 10 60 30
    print("Postorder", bt.postorder());   // 40 50 20 60 30 10
    print("Levelorder", bt.levelorder()); // 10 20 30 40 50 60

    cout << "Size: " << bt.size() << "\n";           // 6
    cout << "Height: " << bt.height() << "\n";       // 2
    cout << "Find 50? " << (bt.find(50) ? "Yes" : "No") << "\n";
    cout << "Is complete? " << (bt.isComplete() ? "Yes" : "No") << "\n";

    return 0;
}
