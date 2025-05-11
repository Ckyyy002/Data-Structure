#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE]; 
    int top;            
} Stack;

void initialize(Stack *STACK) {
    STACK->top = -1;
}

int isEmpty(Stack *STACK) {
    return STACK->top == -1;
}

int isFull(Stack *STACK) {
    return STACK->top == MAX_SIZE - 1;
}

void push(Stack *STACK, int value) {
    if (isFull(STACK)) {
        printf("Stack overflow!\n");
        return;
    }
    STACK->data[++(STACK->top)] = value;
}

int pop(Stack *STACK) {
    if (isEmpty(STACK)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return STACK->data[(STACK->top)--];
}

int peek(Stack *STACK) {
    if (isEmpty(STACK)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return STACK->data[STACK->top];
}

void sort(Stack *S1, Stack *S2) {
    while (!isEmpty(S1)) {
        int temp = pop(S1);

        while (!isEmpty(S2) && peek(S2) > temp) {
            push(S1, pop(S2));
        }

        push(S2, temp);
    }

    while (!isEmpty(S2)) {
        push(S1, pop(S2));
    }
}

void display(Stack *STACK) {
    if (isEmpty(STACK)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack: ");
    for (int i = STACK->top; i >= 0; i--) {
        printf("%d ", STACK->data[i]);
    }
    printf("\n");
}

int main() {
    Stack S1, S2;
    initialize(&S1);
    initialize(&S2);
    int n, value;

    printf("Enter number of elements in the stack: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i+1);
        scanf("%d", &value);
        push(&S1, value);
    }

    sort(&S1, &S2);
    printf("\nSorted stack:\n");
    display(&S1);

    return 0;
}
