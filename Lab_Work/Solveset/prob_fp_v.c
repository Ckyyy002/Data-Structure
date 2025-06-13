#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct bstnode_t {
    int key;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) {
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

BSTNode* __bst__remove(BSTNode *root, int value) {
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
        printf("%d ", root->key);
        __bst__inorder(root->right);
    }
}

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

int bst_depth(BST *bst, int value) {
    BSTNode *node = bst->_root;
    int depth = 1;
    
    while (node != NULL) {
        if (value < node->key) {
            node = node->left;
            depth++;
        } 
        else if (value > node->key) {
            node = node->right;
            depth++;
        } 
        else {
            return depth;
        }
    }
    
    return -1; 
}

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

void bst_inorder(BST *bst) {
    __bst__inorder(bst->_root);
}
 
int main()
{
    BST set;
    bst_init(&set);

    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        char str[10];
        scanf("%s", str);

        int x;
        if(strcmp(str, "INSERT") == 0) {
            scanf("%d", &x);
            bst_insert(&set, x);
        }
        else if(strcmp(str, "DELETE") == 0) {
            scanf("%d", &x);
            bst_remove(&set, x);
        }
        else if(strcmp(str, "SEARCH") == 0) {
            scanf("%d", &x);
            printf("%d\n", bst_depth(&set, x));
        }
        else {
            bool empty = bst_isEmpty(&set);
            if(!empty) {
                bst_inorder(&set);
            }
            else {
                printf("EMPTY");
            }
            printf("\n");
        }
    }
    
    return 0;
}