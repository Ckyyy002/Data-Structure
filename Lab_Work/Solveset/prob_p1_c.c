#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *prev, *next;
} Node;

typedef struct List {
    Node *head, *tail;
    int size;
} List;

void init(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void push(List *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (list->size == 0) {
        list->head = list->tail = newNode;
    } 
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
}

void solve(List *list, int n) {
    Node *current = list->head;

    for (int i = 0; i < n; i++) {
        if (i % 2) {
            printf("%d %d ", current->val, current->prev->val);
        }
        if (current->next != NULL) {
            current = current->next;
        }
    }

    if (n % 2) {
        printf("%d", current->val);
    }

    printf("\n");
}

int main() {
    List *list = (List *)malloc(sizeof(List));
    init(list);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        push(list, value);
    }

    solve(list, n);
    return 0;
}
