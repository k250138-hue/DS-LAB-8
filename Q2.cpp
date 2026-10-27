
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

    void inorder(Node* node) {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    Node* findMin(Node* node) {
        while (node != NULL && node->left != NULL)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int value) {
        if (node == NULL)
            return NULL;

        if (value < node->data)
            node->left = deleteNode(node->left, value);

        else if (value > node->data)
            node->right = deleteNode(node->right, value);

        else {
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        return node;
    }

public:
    BST() {
        root = NULL;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void sort() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        tree.insert(values[i]);
    }

    tree.remove(20);
    cout << "After deleting 20: ";
    tree.sort();

    tree.remove(30);
    cout << "After deleting 30: ";
    tree.sort();

    tree.remove(50);
    cout << "After deleting 50: ";
    tree.sort();

    return 0;
}
