#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct {
    int id;
    int priority;
} Job;

typedef struct {
    Job jobs[MAX_SIZE];
    int size;
} queue;

void q_init(queue *q) { 
    q->size = 0; 
}

int isEmpty(queue *q) { 
    return q->size == 0; 
}

int isFull(queue *q) { 
    return q->size >= MAX_SIZE; 
}

void enqueue(queue *q) {
    if (isFull(q)) {
        printf("Queue full\n");
        return;
    }
    
    Job new;
    printf("Enter job ID and priority: ");
    scanf("%d %d", &new.id, &new.priority);
    
    int i = q->size - 1;
    while (i >= 0 && q->jobs[i].priority < new.priority) {
        q->jobs[i + 1] = q->jobs[i];
        i--;
    }
    
    q->jobs[i + 1] = new;
    q->size++;
    printf("Added job %d (priority %d)\n", new.id, new.priority);
}

void dequeue(queue *q) {
    if (isEmpty(q)) {
        printf("Queue empty\n");
        return;
    }

    q->size--;
    printf("Removed job %d (priority %d)\n", q->jobs[q->size].id, q->jobs[q->size].priority);
}

void remove_job(queue *q) {
    if (isEmpty(q)) {
        printf("Queue empty\n");
        return;
    }

    int id;
    printf("Enter job ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < q->size; i++) {
        if (q->jobs[i].id == id) {
            for (int j = i; j < q->size - 1; j++)
                q->jobs[j] = q->jobs[j + 1];
            q->size--;
            printf("Removed job %d\n", id);
            return;
        }
    }
    printf("Job %d not found\n", id);
}

void display(queue *q) {
    if (isEmpty(q)) {
        printf("Queue empty\n");
        return;
    }

    printf("\nJob Queue:\nID\tPriority\n");
    for (int i = 0; i < q->size; i++) {
        printf("%d\t%d\n", q->jobs[i].id, q->jobs[i].priority);
    }
    printf("\n\n");
}

void menu() {
    printf("Priority Queue Menu:\n");
    printf("1. Enqueue job\n2. Dequeue highest\n3. Remove specific job\n4. Display queue\n5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    queue q;
    q_init(&q);
    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue(&q);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                remove_job(&q);
                break;
            case 4:
                display(&q);
                break;
            case 5:
                printf("Exited the program\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
