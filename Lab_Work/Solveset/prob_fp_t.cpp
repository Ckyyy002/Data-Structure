#include <stdlib.h>
#include <stdio.h>

struct AVLNode {
    int data;
    struct AVLNode *left, *right;
    int height;
};

struct AVL {
    struct AVLNode *_root;
    unsigned _size;

    AVLNode* _avl_createNode(int value) {
        struct AVLNode *newNode = (struct AVLNode*) malloc(sizeof(struct AVLNode));
        newNode->data = value;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    int _getHeight(struct AVLNode* node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int _max(int a, int b) {
        return (a > b) ? a : b;
    }

    AVLNode* _rightRotate(struct AVLNode* pivotNode) {
        struct AVLNode* newParrent = pivotNode->left;
        pivotNode->left = newParrent->right;
        newParrent->right = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
        newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;
        
        return newParrent;
    }

    AVLNode* _leftRotate(struct AVLNode* pivotNode) {
        struct AVLNode* newParrent = pivotNode->right;
        pivotNode->right = newParrent->left;
        newParrent->left = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
        newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;
        
        return newParrent;
    }

    AVLNode* _leftCaseRotate(struct AVLNode* node) {
        printf("Left Case\n");
        printf("PivotNode: %d\n", node->data);
        printf("PivotNode->left: %d\n", node->left->data);
        printf("PivotNode->left->left: %d\n", node->left->left->data);
        struct AVLNode* newRoot = _rightRotate(node);
        printf("\nresult:\n");
        printf("NewNode: %d\n", newRoot->data);
        printf("NewNode->left: %d\n", newRoot->left->data);
        printf("NewNode->right: %d\n", newRoot->right->data);
        printf("\n");
        return newRoot;
    }

    AVLNode* _rightCaseRotate(struct AVLNode* node) {
        printf("Right Case\n");
        printf("PivotNode: %d\n", node->data);
        printf("PivotNode->right: %d\n", node->right->data);
        printf("PivotNode->right->right: %d\n", node->right->right->data);
        struct AVLNode* newRoot = _leftRotate(node);
        printf("\nresult:\n");
        printf("NewNode: %d\n", newRoot->data);
        printf("NewNode->left: %d\n", newRoot->left->data);
        printf("NewNode->right: %d\n", newRoot->right->data);
        printf("\n");
        return newRoot;
    }

    AVLNode* _leftRightCaseRotate(struct AVLNode* node) {
        printf("Left Right Case\n");
        printf("PivotNode: %d\n", node->data);
        printf("PivotNode->left: %d\n", node->left->data);
        printf("PivotNode->left->right: %d\n", node->left->right->data);
        node->left = _leftRotate(node->left);
        struct AVLNode* newRoot = _rightRotate(node);
        printf("\nresult:\n");
        printf("NewNode: %d\n", newRoot->data);
        printf("NewNode->left: %d\n", newRoot->left->data);
        printf("NewNode->right: %d\n", newRoot->right->data);
        printf("\n");
        return newRoot;
    }

    AVLNode* _rightLeftCaseRotate(struct AVLNode* node) {
        printf("Right Left Case\n");
        printf("PivotNode: %d\n", node->data);
        printf("PivotNode->right: %d\n", node->right->data);
        printf("PivotNode->right->left: %d\n", node->right->left->data);
        node->right = _rightRotate(node->right);
        struct AVLNode* newRoot = _leftRotate(node);
        printf("\nresult:\n");
        printf("NewNode: %d\n", newRoot->data);
        printf("NewNode->left: %d\n", newRoot->left->data);
        printf("NewNode->right: %d\n", newRoot->right->data);
        printf("\n");
        return newRoot;
    }

    int _getBalanceFactor(struct AVLNode* node) {
        return _getHeight(node->left) - _getHeight(node->right);
    }

    AVLNode* _insert_AVL(struct AVLNode* node, int value) {
        if (node == NULL)
            return _avl_createNode(value);
        if (value < node->data)
            node->left = _insert_AVL(node->left, value);
        else if (value > node->data)
            node->right = _insert_AVL(node->right, value);
        
        node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));

        int balanceFactor = _getBalanceFactor(node);
        
        if (balanceFactor > 1 && value < node->left->data)
            return _leftCaseRotate(node);
        if (balanceFactor > 1 && value > node->left->data)
            return _leftRightCaseRotate(node);
        if (balanceFactor < -1 && value > node->right->data)
            return _rightCaseRotate(node);
        if (balanceFactor < -1 && value < node->right->data)
            return _rightLeftCaseRotate(node);
        
        return node;
    }

    void _inorder(struct AVLNode *node) {
        if (node) {
            _inorder(node->left);
            _inorder(node->right);
        }
    }

    void init() {
        _root = NULL;
        _size = 0;
    }

    void insert(int value) {
        _root = _insert_AVL(_root, value);
        _size++;
    }

    void inorder() {
        this->_inorder(_root);
    }
};

int main(int argc, char const *argv[]) {
    struct AVL set;
    set.init();

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        set.insert(a);
    }

    set.inorder();

    return 0;
}