#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

Node *insert(Node *root, int val) {
    if (root == NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (val < root->val) {
        root->left = insert(root->left, val);
    } 
    else {
        root->right = insert(root->right, val);
    }

    return root;
}

Node *delete_successor(Node *root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }

    if (root->right == NULL) {
        Node *newRoot = root->left;
        free(root);
        return newRoot;
    }

    if (root->left == NULL) {
        Node *newRoot = root->right;
        free(root);
        return newRoot;
    }

    Node *parent = NULL;
    Node *successor = root->right;
    while (successor->left != NULL) {
        parent = successor;
        successor = successor->left;
    }

    if (parent != NULL) {
        parent->left = successor->right;
    } 
    else {
        root->right = successor->right;
    }

    successor->left = root->left;
    successor->right = root->right;

    free(root);
    return successor;
}

Node *delete_predecessor(Node *root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }

    if (root->right == NULL) {
        Node *newRoot = root->left;
        free(root);
        return newRoot;
    }

    if (root->left == NULL) {
        Node *newRoot = root->right;
        free(root);
        return newRoot;
    }

    Node *parent = NULL;
    Node *predecessor = root->left;
    while (predecessor->right != NULL) {
        parent = predecessor;
        predecessor = predecessor->right;
    }

    if (parent != NULL) {
        parent->right = predecessor->left;
    } 
    else {
        root->left = predecessor->left;
    }

    predecessor->left = root->left;
    predecessor->right = root->right;

    free(root);
    return predecessor;
}

void in_order(Node *root) {
    if (root == NULL) {
        return;
    }

    in_order(root->left);
    printf("%d ", root->val);
    in_order(root->right);
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int values[n];
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("Original tree in-order: ");
    in_order(root);
    printf("\n");

    Node *new_successor = delete_successor(root);
    printf("After deleting root with successor: ");
    in_order(new_successor);
    printf("\n");

    freeTree(new_successor);

    root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    Node *new_predecessor = delete_predecessor(root);
    printf("After deleting root with predecessor: ");
    in_order(new_predecessor);
    printf("\n");

    freeTree(new_predecessor);

    return 0;
}
