14_147.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int val) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *search_pre(Node *root, int key) {
    Node *find_node = search_pre(root->left, key);

    if (root == NULL) {
        return NULL;
    }

    if (root->val == key) {
        return root;
    }

    if (find_node != NULL) {
        return find_node;
    }

    return search_pre(root->right, key);
}

Node *search_in(Node *root, int key) {
    Node *find_node = search_in(root->left, key);

    if (root == NULL) {
        return NULL;
    }

    if (find_node != NULL) {
        return find_node;
    }

    if (root->val == key) {
        return root;
    }

    return search_in(root->right, key);
}

Node *search_post(Node *root, int key) {
    Node *find_node;
    if (root == NULL) {
        return NULL;
    }
    
    find_node = search_post(root->left, key);
    if (find_node != NULL) {
        return find_node;
    }

    find_node = search_post(root->right, key);
    if (find_node != NULL) {
        return find_node;
    }

    if (root->val == key) {
        return root;
    }

    return NULL;
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
    int key;
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    Node* resultPreOrder = search_pre(root, key);
    if (resultPreOrder != NULL) {
        printf("Pre-order search: Found\n");
    } 
    else {
        printf("Pre-order search: Not Found\n");
    }

    Node* resultInOrder = search_in(root, key);
    if (resultInOrder != NULL) {
        printf("In-order search: Found\n");
    } 
    else {
        printf("In-order search: Not Found\n");
    }

    Node* resultPostOrder = search_post(root, key);
    if (resultPostOrder != NULL) {
        printf("Post-order search: Found\n");
    } 
    else {
        printf("Post-order search: Not Found\n");
    }

    freeTree(root);

    return 0;
}
