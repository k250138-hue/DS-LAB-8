
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

class BST {
private:
    Node* root;

    Node* insertNode(Node* node, int value) {
        if (node == NULL)
            return new Node(value);

        if (value < node->data)
            node->left = insertNode(node->left, value);
        else if (value > node->data)
            node->right = insertNode(node->right, value);

        return node;
    }

    void preorder(Node* node) {
        if (node == NULL)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(Node* node) {
        if (node == NULL)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    int countOneChild(Node* node) {
        if (node == NULL)
            return 0;

        int count = 0;

        if ((node->left == NULL && node->right != NULL) ||
            (node->left != NULL && node->right == NULL))
            count = 1;

        return count + countOneChild(node->left)
                     + countOneChild(node->right);
    }

    int countTwoChildren(Node* node) {
        if (node == NULL)
            return 0;

        int count = 0;

        if (node->left != NULL && node->right != NULL)
            count = 1;

        return count + countTwoChildren(node->left)
                     + countTwoChildren(node->right);
    }

    int height(Node* node) {
        if (node == NULL)
            return -1;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;

        return rightHeight + 1;
    }

public:
    BST() {
        root = NULL;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void displayPreorder() {
        preorder(root);
        cout << endl;
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }

    void displayPostorder() {
        postorder(root);
        cout << endl;
    }

    void displayOneChildCount() {
        cout << countOneChild(root) << endl;
    }

    void displayTwoChildrenCount() {
        cout << countTwoChildren(root) << endl;
    }

    void displayHeight() {
        cout << height(root) << endl;
    }
};

int main() {
    BST tree;

    int scores[] = {45, 25, 65, 15, 35, 55, 75, 30};
    int n = sizeof(scores) / sizeof(scores[0]);

    for (int i = 0; i < n; i++) {
        tree.insert(scores[i]);
    }

    cout << "Preorder: ";
    tree.displayPreorder();

    cout << "Inorder: ";
    tree.displayInorder();

    cout << "Postorder: ";
    tree.displayPostorder();

    cout << "Nodes with one child: ";
    tree.displayOneChildCount();

    cout << "Nodes with two children: ";
    tree.displayTwoChildrenCount();

    cout << "Height (edges): ";
    tree.displayHeight();

    return 0;
}
