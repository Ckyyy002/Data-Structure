#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void push(Queue *q, int val) {
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

int pop(Queue *q) {
    if (q->head == NULL) {
        return -1;
    }

    Node *temp = q->head;
    int val = temp->val;
    q->head = q->head->next;
    free(temp);

    if (q->head == NULL) {
        q->tail = NULL;
    }

    return val;
}

void print(Queue *q) {
    Node *current = q->head;
    if (current == NULL) {
        printf("KOSONG");
    }
    else{
        while (current != NULL) {
            printf("%d ", current->val);
            current = current->next;
        }
    }
    printf("\n");
}

int main() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    init(queue);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int input;
        scanf("%d", &input);
        push(queue, input);
    }

    int s;
    scanf("%d", &s);
    for (int i = 0; i < s; i++) {
        char str[10];
        scanf("%s", str);
        if (strcmp(str, "BERHASIL") == 0) {
            pop(queue);
        }
        else if (strcmp(str, "GAGAL") == 0) {
            int x = pop(queue);
            if (x != -1) {
                push(queue, x);
            }
        }
    }

    print(queue);

    return 0;
}
