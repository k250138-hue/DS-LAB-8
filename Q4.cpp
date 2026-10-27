
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

    Node* findMax(Node* node) {
        while (node != NULL && node->right != NULL)
            node = node->right;

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

    void displayGreaterThan(Node* node, double threshold) {
        if (node == NULL)
            return;

        displayGreaterThan(node->left, threshold);

        if (node->data > threshold)
            cout << node->data << " ";

        displayGreaterThan(node->right, threshold);
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

    void displayLongestPath(Node* node) {
        while (node != NULL) {
            cout << node->data << " ";

            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            if (leftHeight == -1 && rightHeight == -1)
                break;

            if (leftHeight >= rightHeight)
                node = node->left;
            else
                node = node->right;
        }
    }

    bool isSkewed(Node* node) {
        if (node == NULL)
            return true;

        if (node->left != NULL && node->right != NULL)
            return false;

        return isSkewed(node->left) && isSkewed(node->right);
    }

    Node* deleteOneChildNodes(Node* node, int& deletedCount) {
        if (node == NULL)
            return NULL;

        bool oneChild = (node->left == NULL && node->right != NULL) ||
                        (node->left != NULL && node->right == NULL);

        node->left = deleteOneChildNodes(node->left, deletedCount);
        node->right = deleteOneChildNodes(node->right, deletedCount);

        if (oneChild) {
            int value = node->data;
            node = deleteNode(node, value);
            deletedCount++;
        }

        return node;
    }

    void kthSmallest(Node* node, int k, int& count,
                     int& result, bool& found) {
        if (node == NULL || found)
            return;

        kthSmallest(node->left, k, count, result, found);

        if (found)
            return;

        count++;

        if (count == k) {
            result = node->data;
            found = true;
            return;
        }

        kthSmallest(node->right, k, count, result, found);
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

    int getMin() {
        Node* temp = findMin(root);

        if (temp == NULL)
            return -1;

        return temp->data;
    }

    int getMax() {
        Node* temp = findMax(root);

        if (temp == NULL)
            return -1;

        return temp->data;
    }

    void showGreaterThan(double threshold) {
        displayGreaterThan(root, threshold);
        cout << endl;
    }

    int getTwoChildrenCount() {
        return countTwoChildren(root);
    }

    int getHeight() {
        return height(root);
    }

    void showLongestPath() {
        displayLongestPath(root);
        cout << endl;
    }

    bool checkSkewed() {
        return isSkewed(root);
    }

    int removeOneChildNodes() {
        int deletedCount = 0;
        root = deleteOneChildNodes(root, deletedCount);
        return deletedCount;
    }

    bool getKthSmallest(int k, int& result) {
        int count = 0;
        bool found = false;

        if (k <= 0)
            return false;

        kthSmallest(root, k, count, result, found);

        return found;
    }
};

int main() {
    BST tree;

    tree.insert(45);
    tree.insert(25);
    tree.insert(65);
    tree.insert(15);
    tree.insert(35);
    tree.insert(55);
    tree.insert(75);
    tree.insert(10);
    tree.insert(30);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(32);
    tree.insert(33);

    int k = 4;

    cout << "Original inorder: ";
    tree.sort();

    int minimum = tree.getMin();
    int maximum = tree.getMax();

    cout << "Minimum marks: " << minimum << endl;
    cout << "Maximum marks: " << maximum << endl;

    double threshold = (minimum + maximum) / 2.0;

    cout << "Threshold: " << threshold << endl;

    cout << "Marks greater than threshold: ";
    tree.showGreaterThan(threshold);

    cout << "Nodes with two children: ";
    cout << tree.getTwoChildrenCount() << endl;

    cout << "Longest root-to-leaf path: ";
    tree.showLongestPath();

    cout << "Height (edges): " << tree.getHeight() << endl;

    cout << "Is tree skewed? ";
    if (tree.checkSkewed())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    int deletedCount = tree.removeOneChildNodes();

    cout << "Number of nodes deleted: ";
    cout << deletedCount << endl;

    cout << "Final inorder: ";
    tree.sort();

    int result;

    if (tree.getKthSmallest(k, result))
        cout << k << "th smallest remaining mark: "
             << result << endl;
    else
        cout << "Invalid k" << endl;

    return 0;
}
