#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t {
    long key;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(long value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, long value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

void __bst__preorder(BSTNode *root, long *arr, int *index) {
    if (root) {
        arr[(*index)++] = root->key;
        __bst__preorder(root->left, arr, index);
        __bst__preorder(root->right, arr, index);
    }
}

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0;
}

void bst_insert(BST *bst, long value) {
    bst->_root = __bst__insert(bst->_root, value);
    bst->_size++;
}

void bst_preorder(BST *bst, long *arr, int index) {
    __bst__preorder(bst->_root, arr, &index);
}
 
int main() {
    BST set;
    bst_init(&set);

    int n;
    scanf("%d", &n);

    long a[n];
    for(int i = 0; i < n; i++){
        scanf("%ld", &a[i]);
        bst_insert(&set, a[i]);
    }

    long arr[n];
    int index = 0;
    bst_preorder(&set, arr, index);

    bool same = true;
    for(int i = 0; i < n; i++) {
        if(a[i] != arr[i]) {
            same = false;
            break;
        }
    }

    if(same) {
        printf("Ini pohon\n");
    } 
    else {
        printf("Ini bukan pohon\n");
    }

    return 0;
}