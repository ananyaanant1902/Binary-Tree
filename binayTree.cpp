struct Node{
    int data;
    Node *left, *right;
};

Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree(vector<int>& arr, int index) {
    if (index >= arr.size()) 
        return NULL;

    Node* root = createNode(arr[index]);
    root->left  = buildTreeFromArray(arr, 2 * index + 1);
    root->right = buildTreeFromArray(arr, 2 * index + 2);
    return root;
}

// Preorder traversal
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};

    Node* root = buildTreeFromArray(arr, 0);

    cout << "Preorder Traversal: ";
    preorder(root);
    cout << endl;

    return 0;
}
