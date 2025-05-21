#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct AVLNode_t {
    long long data;
    struct AVLNode_t *left, *right;
    int height;
} AVLNode;

typedef struct AVL_t {
    AVLNode *_root;
    unsigned int _size;
} AVL;

int _max(int a, int b) {
    return (a > b) ? a : b;
}

int _getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int _getBalanceFactor(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return _getHeight(node->left) - _getHeight(node->right);
}

AVLNode* _createNode(int value) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _findMinNode(AVLNode* node) {
    AVLNode* currNode = node;
    while (currNode && currNode->left != NULL) {
        currNode = currNode->left;
    }
    return currNode;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {
    AVLNode* newParent = pivotNode->left;
    pivotNode->left = newParent->right;
    newParent->right = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left),  _getHeight(pivotNode->right)) + 1;
    newParent->height = _max(_getHeight(newParent->left), _getHeight(newParent->right)) + 1;
    
    return newParent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {
    AVLNode* newParent = pivotNode->right;
    pivotNode->right = newParent->left;
    newParent->left = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParent->height = _max(_getHeight(newParent->left), _getHeight(newParent->right)) + 1;
    
    return newParent;
}

AVLNode* _leftCaseRotate(AVLNode* node) {
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node) {
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node) {
    node->left = _leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node) {
    node->right = _rightRotate(node->right);
    return _leftRotate(node);
}

AVLNode* _search(AVLNode* root, long long value, int find) {
    while (root != NULL) {
        if (find == 1) {
            printf("%d ", root->data);
        }
        if (value < root->data) {
            root = root->left;
        }
        else if (value > root->data) {
            root = root->right;
        }
        else {
            return root;
        }
    }
    return NULL;
}

AVLNode* _insert_AVL(AVL* avl, AVLNode* node, long long value) {
    if (node == NULL) {
        return _createNode(value);
    }
    
    if (value < node->data) {
        node->left = _insert_AVL(avl, node->left, value);
    }
    else if (value > node->data) {
        node->right = _insert_AVL(avl, node->right, value);
    }
    
    node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));
    
    int balanceFactor = _getBalanceFactor(node);
    
    if (balanceFactor > 1 && value < node->left->data) {
        return _leftCaseRotate(node);
    }
    if (balanceFactor > 1 && value > node->left->data) {
        return _leftRightCaseRotate(node);
    }
    if (balanceFactor < -1 && value > node->right->data) {
        return _rightCaseRotate(node);
    }
    if (balanceFactor < -1 && value < node->right->data) {
        return _rightLeftCaseRotate(node);
    }
    
    return node;
}

AVLNode* _remove_AVL(AVLNode* node, long long value) {
    if (node == NULL) {
        return node;
    }
    
    if (value > node->data) {
        node->right = _remove_AVL(node->right, value);
    }
    else if (value < node->data) {
        node->left = _remove_AVL(node->left, value);
    }
    else {
        AVLNode* temp;
        if ((node->left == NULL) || (node->right == NULL)) {
            temp = NULL;
            if (node->left == NULL) {
                temp = node->right;
            }
            else if (node->right == NULL) {
                temp = node->left;
            }
            
            if (temp == NULL) {
                temp = node;
                node = NULL;
            }
            else {
                *node = *temp;
            }
            
            free(temp);
        }
        else {
            temp = _findMinNode(node->right);
            node->data = temp->data;
            node->right = _remove_AVL(node->right, temp->data);
        }
    }

    if (node == NULL) {
        return node;
    }
    
    node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));
    
    int balanceFactor = _getBalanceFactor(node);
    
    if (balanceFactor > 1 && _getBalanceFactor(node->left) >= 0) {
        return _leftCaseRotate(node);
    }
    if (balanceFactor > 1 && _getBalanceFactor(node->left) < 0) {
        return _leftRightCaseRotate(node);
    }
    if (balanceFactor < -1 && _getBalanceFactor(node->right) <= 0) {
        return _rightCaseRotate(node);
    }
    if (balanceFactor < -1 && _getBalanceFactor(node->right) > 0) {
        return _rightLeftCaseRotate(node);
    }
    
    return node;
}

void avl_init(AVL* avl) {
    avl->_root = NULL;
    avl->_size = 0;
}

bool avl_isEmpty(AVL* avl) {
    return avl->_root == NULL;
}

bool avl_find(AVL* avl, long long value) {
    AVLNode* temp = _search(avl->_root, value, 0);
    if (temp == NULL) {
        return false;
    }
    
    if (temp->data == value) {
        return true;
    }
    else {
        return false;
    }
}

void avl_insert(AVL* avl, long long value) {
    if(avl_find(avl, value)) {
        printf("%d is already in the tree\n", value);
        return;
    }
    else {
        avl->_root = _insert_AVL(avl, avl->_root, value);
        printf("%d inserted\n", value);
        avl->_size++;
    }
}

void avl_remove(AVL* avl, long long value) {
    if (avl_find(avl, value)) {
        avl->_root = _remove_AVL(avl->_root, value);
        printf("%d deleted\n", value);
        avl->_size--;
    }
    else {
        printf("%d is not found in the tree\n", value);
    }
}

int main() {
    AVL avl;
    avl_init(&avl);

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        char cmd[10];
        long long value;
        scanf("%s %lld", cmd, &value);
        
        if(strcmp(cmd, "INSERT") == 0) {
            avl_insert(&avl, value);
        } 
        else if (strcmp(cmd, "DELETE") == 0) {
            avl_remove(&avl, value);
        } 
        else if (strcmp(cmd, "FIND") == 0) {
            AVLNode* found = _search(avl._root, value, 0);
            if (found != NULL && found->data == value) {
                printf("%lld found with path: ", value);
                _search(avl._root, value, 1);
            } 
            else {
                printf("%lld not found", value);
            }
            printf("\n");
        } 
    }
}