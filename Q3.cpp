
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

    bool searchNode(Node* node, int value) {
        if (node == NULL)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return searchNode(node->left, value);

        return searchNode(node->right, value);
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

    void displayRange(Node* node, int L, int R) {
        if (node == NULL)
            return;

        if (node->data > L)
            displayRange(node->left, L, R);

        if (node->data >= L && node->data <= R)
            cout << node->data << " ";

        if (node->data < R)
            displayRange(node->right, L, R);
    }

    int countRange(Node* node, int L, int R) {
        if (node == NULL)
            return 0;

        if (node->data < L)
            return countRange(node->right, L, R);

        if (node->data > R)
            return countRange(node->left, L, R);

        return 1 + countRange(node->left, L, R)
                 + countRange(node->right, L, R);
    }

    Node* deleteOutsideRange(Node* node, int L, int R) {
        if (node == NULL)
            return NULL;

        node->left = deleteOutsideRange(node->left, L, R);
        node->right = deleteOutsideRange(node->right, L, R);

        if (node->data < L)
            return deleteNode(node, node->data);

        if (node->data > R)
            return deleteNode(node, node->data);

        return node;
    }

    void clear(Node* node) {
        if (node == NULL)
            return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        clear(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    bool search(int value) {
        return searchNode(root, value);
    }

    void sort() {
        inorder(root);
        cout << endl;
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void showRange(int L, int R) {
        displayRange(root, L, R);
        cout << endl;
    }

    int getRangeCount(int L, int R) {
        return countRange(root, L, R);
    }

    void removeOutsideRange(int L, int R) {
        root = deleteOutsideRange(root, L, R);
    }
};

int main() {
    BST tree;

    int ids[] = {50, 25, 75, 10, 30, 60, 90, 20, 40, 70, 80};
    int n = sizeof(ids) / sizeof(ids[0]);

    for (int i = 0; i < n; i++) {
        tree.insert(ids[i]);
    }

    int L = 25;
    int R = 70;

    cout << "IDs in range: ";
    tree.showRange(L, R);

    cout << "Count: ";
    cout << tree.getRangeCount(L, R) << endl;

    tree.removeOutsideRange(L, R);

    cout << "After deleting outside range: ";
    tree.sort();

    return 0;
}
