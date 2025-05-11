#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

typedef struct {
    Stack enqueue_stack;
    Stack dequeue_stack;
} Queue;

void s_init(Stack* s) { 
    s->top = -1; 
}

int s_empty(Stack* s) { 
    return s->top == -1; 
}

int s_full(Stack* s) { 
    return s->top >= MAX_SIZE - 1; 
}

void s_push(Stack* s, int item) {
    s->data[++s->top] = item;
}

int s_pop(Stack* s) {
    if (s_empty(s)) { 
        printf("Queue empty\n\n"); 
        return -1; 
    }
    return s->data[s->top--];
}

void q_init(Queue* q) {
    s_init(&q->enqueue_stack);
    s_init(&q->dequeue_stack);
}

void transfer(Queue* q) {
    while (!s_empty(&q->enqueue_stack)) {
        s_push(&q->dequeue_stack, s_pop(&q->enqueue_stack));
    }
}

void q_clear(Queue* q) {
    q_init(q);
    printf("Queue cleared\n\n");
}

int q_empty(Queue* q) {
    return s_empty(&q->enqueue_stack) && s_empty(&q->dequeue_stack);
}

void q_display(Queue* q) {
    if (q_empty(q)) { 
        printf("Queue empty\n\n"); 
        return; 
    }
    
    printf("Queue: ");
    for (int i = q->dequeue_stack.top; i >= 0; i--) {
        printf("%d ", q->dequeue_stack.data[i]);
    }
    
    for (int i = 0; i <= q->enqueue_stack.top; i++) {
        printf("%d ", q->enqueue_stack.data[i]);
    }
    printf("\n\n");
}

void enqueue(Queue* q, int item) {
    int total_elements = (q->enqueue_stack.top + 1) + (q->dequeue_stack.top + 1);
    
    if (total_elements >= MAX_SIZE) {
        printf("Queue full\n\n");
        return;
    }
    
    s_push(&q->enqueue_stack, item);
    printf("Enqueued %d\n\n", item);
}

int dequeue(Queue* q) {
    if (s_empty(&q->dequeue_stack)) {
        transfer(q);
    }
    
    if (s_empty(&q->dequeue_stack)) {
        printf("Queue empty\n\n");
        return -1;
    }
    
    printf("Dequeued %d\n\n", q->dequeue_stack.data[q->dequeue_stack.top]);
    return s_pop(&q->dequeue_stack);
}

void menu() {
    printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Clear\n5. Exit\n");
    printf("Choice: ");
}

int main() {
    Queue q;
    q_init(&q);
    int choice, item;
    
    while (1) {
        menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &item);
                enqueue(&q, item);
                break;
            case 2: 
                dequeue(&q); 
                break;
            case 3: 
                q_display(&q); 
                break;
            case 4: 
                q_clear(&q); 
                break;
            case 5: 
                printf("Exited the program\n"); 
                return 0;
            default: 
                printf("Invalid choice\n");
        }
    }
}
