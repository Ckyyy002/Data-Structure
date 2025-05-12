#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head, *tail;
} Queue;

void init(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(Queue *q, int val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = NULL;

    if (q->head == NULL) {
        q->head = q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

void solve(Queue *q, int y, int z, int *ans1, int *ans2) {
    Node *current = q->head;
    while (current != NULL) {
        if (y > current->val) {
            (*ans1)++;
            y -= current->val;
        }
        if (y >= z) {
            (*ans2)++;
        }
        current = current->next;
    }
}

int main() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    init(queue);

    int x, y, z, input;
    int ans1 = 0, ans2 = 0;

    scanf("%d %d %d", &x, &y, &z);
    for (int i = 0; i < x; i++) {
        scanf("%d", &input);
        enqueue(queue, input);
    }

    solve(queue, y, z, &ans1, &ans2);

    printf("%d ", ans2 - (ans2 == x));
    if (ans1 == x) {
        printf("Yes Dapat burger gratis!!!\n");
    } 
    else {
        printf("NOO tidak Dapat :(\n");
    }

    return 0;
}
