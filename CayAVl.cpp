#include <iostream>
using namespace std;

// Cau truc cua mot node trong cay AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Ham de lay chieu cao cua mot node
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Ham de lay gia tri lon hon giua hai so
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Ham de tao mot node moi
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // chieu cao khoi tao la 1
    return node;
}

// Ham de xoay phai
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Thuc hien xoay
    x->right = y;
    y->left = T2;

    // Cap nhat chieu cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Tra ve node moi
    return x;
}

// Ham de xoay trai
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Thuc hien xoay
    y->left = x;
    x->right = T2;

    // Cap nhat chieu cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Tra ve node moi
    return y;
}

// Ham de lay do can bang cua mot node
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Ham de them mot node vao cay AVL
Node* insert(Node* node, int key) {
    // Buoc 1: Thuc hien chen nhu trong cay nhi phan
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Khong cho phep chen cac gia tri trung lap
        return node;

    // Buoc 2: Cap nhat chieu cao cua node cha
    node->height = 1 + max(height(node->left), height(node->right));

    // Buoc 3: Kiem tra do can bang cua node
    int balance = getBalance(node);

    // Neu node bi mat can bang, co 4 truong hop

    // Truong hop trai trai
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Truong hop phai phai
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Truong hop trai phai
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Truong hop phai trai
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Tra ve node khong thay doi
    return node;
}

// Ham de tim node co gia tri nho nhat
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Ham de xoa mot node khoi cay AVL
Node* deleteNode(Node* root, int key) {
    // Buoc 1: Thuc hien xoa nhu trong cay nhi phan
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node nay la node can xoa
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root ->left ? root->left : root->right;

            // Khong co con
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // Co mot con
                *root = *temp; // Sao chep noi dung cua node con
            delete temp;
        } else {
            // Node co hai con: lay gia tri nho nhat trong cay ben phai
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            // Xoa node nho nhat
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Neu cay chi con mot node
    if (root == NULL)
        return root;

    // Buoc 2: Cap nhat chieu cao cua node cha
    root->height = 1 + max(height(root->left), height(root->right));

    // Buoc 3: Kiem tra do can bang cua node
    int balance = getBalance(root);

    // Neu node bi mat can bang, co 4 truong hop

    // Truong hop trai trai
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Truong hop trai phai
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Truong hop phai phai
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Truong hop phai trai
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Ham de duyet cay theo thu tu
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// Ham de duyet cay theo tien thu tu
void preOrder(Node* root) {
    if (root != NULL) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Ham de duyet cay theo hau thu tu
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

// Ham chinh
int main() {
    Node* root = NULL;

    // Them cac node vao cay
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Duyet cay
    cout << "Duyet cay theo thu tu: ";
    inOrder(root);
    cout << endl;

    // Xoa mot node
    root = deleteNode(root, 10);
    cout << "Duyet cay sau khi xoa 10: ";
    inOrder(root);
    cout << endl;

    return 0;
}
