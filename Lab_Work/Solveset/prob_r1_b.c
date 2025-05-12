#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node{
    unsigned long long data;
    struct Node *next;
} Node;

typedef struct Queue{
    Node *head, *tail;
} Queue;

void init(Queue *queue){
    queue->head = NULL;
    queue->tail = NULL;
}

void push(Queue *queue, unsigned long long value){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if(queue->head == NULL){
        queue->head = newNode;
        queue->tail = newNode;
    }
    else if(queue->head->data < value){
        newNode->next = queue->head;
        queue->head = newNode;
    }
    else{
        Node *current = queue->head;
        while(current->next != NULL && current->next->data > value){
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

unsigned long long pop(Queue *queue){
    if(queue->head == NULL){
        return -1;
    }

    Node *temp = queue->head;
    unsigned long long value = temp->data;
    queue->head = queue->head->next;
    free(temp);

    if(queue->head == NULL){
        queue->tail = NULL;
    }

    return value;
}

int main(){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    init(queue);

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        unsigned long long value;
        scanf("%llu", &value);
        push(queue, value);
    }

    while(queue->head != NULL && queue->head->next != NULL){
        unsigned long long value1 = pop(queue);
        unsigned long long value2 = pop(queue);
        unsigned long long diff = abs(value1 - value2);

        if(diff != 0){
            push(queue, diff);
        }
    }

    if(queue->head != NULL){
        printf("%llu\n", queue->head->data);
    }
    else{
        printf("0\n");
    }
    free(queue);
}