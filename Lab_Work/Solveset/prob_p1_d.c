#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *top;
} Queue;

void init(Queue *pq) {
    pq->top = NULL;
}

int translate(char c) {
    switch (c) {
        case ')': return 0;
        case '!': return 1;
        case '@': return 2;
        case '#': return 3;
        case '$': return 4;
        case '%': return 5;
        case '^': return 6;
        case '&': return 7;
        case '*': return 8;
        case '(': return 9;
        default: return -1;
    }
}

void push(Queue *pq, int value, int *target) {
    if (value > *target) {
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = value;
    newNode->next = NULL;

    if (pq->top == NULL || pq->top->val < value) {
        newNode->next = pq->top;
        pq->top = newNode;
    } 
    else {
        Node *current = pq->top;
        while (current->next != NULL && current->next->val > value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    while (pq->top != NULL && pq->top->val == *target) {
        printf("%d ", pq->top->val);
        Node *temp = pq->top;
        pq->top = pq->top->next;
        free(temp);
        (*target)--;
    }

    printf("\n");
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Queue *pq = (Queue *)malloc(sizeof(Queue));
    init(pq);

    for (int i = 0; i < n; i++) {
        char token[6];
        scanf("%s", token);

        int value = 0;
        for (int j = 0; j < strlen(token); j++) {
            value = value * 10 + translate(token[j]);
        }

        push(pq, value, &m);
    }

    return 0;
}
