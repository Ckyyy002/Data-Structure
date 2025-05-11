#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct {
    int data[MAX_SIZE];
    int head, tail, count;
} circular;

void initialize(circular *queue) {
    queue->head = queue->count = 0;
    queue->tail = -1;
}

int isEmpty(circular *queue) { 
    return queue->count == 0; 
}

int isFull(circular *queue) { 
    return queue->count == MAX_SIZE; 
}

int enqueue(circular *queue, int value) {
    queue->tail = (queue->tail + 1) % MAX_SIZE;
    queue->data[queue->tail] = value;
    queue->count++;
    return 1;
}

int dequeue(circular *queue, int *value) {
    *value = queue->data[queue->head];
    queue->head = (queue->head + 1) % MAX_SIZE;
    queue->count--;
    return 1;
}

void show(circular *queue) {
    printf("Queue: ");
    int index;
    for (int i = 0; i < queue->count; i++) {
        index = (queue->head + i) % MAX_SIZE;
        printf("%d ", queue->data[index]);
    }
    printf("\n\n");
}

int find(circular *queue, int value) {
    int index;
    for (int i = 0; i < queue->count; i++) {
        index = (queue->head + i) % MAX_SIZE;
        if (queue->data[index] == value) {
            printf("%d found\n\n", value);
            return index;
        }
    }
    
    printf("%d not found\n\n", value);
    return -1;
}

int edit(circular *queue, int oldVal, int newVal) {
    int idx = find(queue, oldVal);

    if (idx == -1) {
        return 0;
    }

    queue->data[idx] = newVal;
    printf("Changed %d to %d\n\n", oldVal, newVal);
    return 1;
}

void clear(circular *queue) {
    initialize(queue);
    printf("Queue cleared\n\n");
}

void menu() {
    printf("QUEUE MENU\n");
    printf("1. Enqueue\n2. Dequeue\n3. Show\n4. Find\n5. Edit\n6. Clear\n7. Exit\n");
    printf("Choice: ");
}

int main() {
    circular queue;
    initialize(&queue);
    int choice, val, oldVal, newVal;

    while (1) {
        menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if (isFull(&queue)) {
                    printf("Queue is full!\n\n");
                    break;
                } 
                printf("Value to enqueue: ");
                scanf("%d", &val);
                enqueue(&queue, val);
                printf("Enqueued %d\n\n", val);
                break;
            case 2: 
                if (isEmpty(&queue)) {
                    printf("Queue is empty!\n\n");
                    break;
                }
                if (dequeue(&queue, &val)) {
                    printf("%d dequeued\n\n", val);
                }
                break;
            case 3: 
                if (isEmpty(&queue)) {
                    printf("Queue is empty!\n\n");
                    break;
                }
                show(&queue); 
                break;
            case 4: 
                if (isEmpty(&queue)) {
                    printf("Queue is empty!\n\n");
                    break;
                }
                printf("Value to find: ");
                scanf("%d", &val);
                find(&queue, val);
                break;
            case 5: 
                if (isEmpty(&queue)) {
                    printf("Queue is empty!\n\n");
                    break;
                }
                printf("Value to edit: ");
                scanf("%d", &oldVal);
                printf("New value: ");
                scanf("%d", &newVal);
                edit(&queue, oldVal, newVal);
                break;
            case 6: 
                clear(&queue); 
                break;
            case 7: 
                printf("Exited the program\n"); 
                return 0;
            default: 
                printf("Invalid choice!\n\n");
        }
    }
}
