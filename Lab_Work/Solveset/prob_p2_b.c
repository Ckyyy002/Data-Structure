#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct bstnode_t {
    long long key;
    int count;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(long long value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, long long value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, long long value) {
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, long long value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

void __bst__inorder(BSTNode *root) {
    if (root) {
        __bst__inorder(root->left);
        printf("%lld(%d) ", root->key, root->count);
        __bst__inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root) {
    if (root) {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%lld(%d) ", root->key, root->count);
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%lld(%d) ", root->key, root->count);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

bool bst_find(BST *bst, long long value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, long long value) {
    BSTNode *node = __bst__search(bst->_root, value);
    if (node == NULL) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
    else {
        node->count++;
    }
}

void bst_remove(BST *bst, long long value) {
    BSTNode *node = __bst__search(bst->_root, value);
    if (node != NULL) {
        if (node->count > 1) {
            node->count--;
        } 
        else {
            bst->_root = __bst__remove(bst->_root, value);
            bst->_size--;
        }
    }
}

void bst_inorder(BST *bst) {
    __bst__inorder(bst->_root);
}

void bst_postorder(BST *bst) {
    __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst) {
    __bst__preorder(bst->_root);
}
 
int main() {
    BST set;
    bst_init(&set);

    int n;
    long long value;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char cmd[10];
        scanf("%s %lld", cmd, &value);

        if (strcmp(cmd, "insert") == 0) {
            bst_insert(&set, value);
        } 
        else if (strcmp(cmd, "remove") == 0) {
            bst_remove(&set, value);
        } 
        else if (strcmp(cmd, "inorder") == 0) {
            bst_inorder(&set);
            printf("\n");
        } 
        else if (strcmp(cmd, "preorder") == 0) {
            bst_preorder(&set);
            printf("\n");
        } 
        else if (strcmp(cmd, "postorder") == 0) {
            bst_postorder(&set);
            printf("\n");
        }
    }
    
    return 0;
}