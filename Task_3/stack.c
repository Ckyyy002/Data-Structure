#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 10

typedef struct {
    int top;
    int data[MAX_STACK];
} stack;

void inisialisasi(stack *STACK) {
    STACK->top = -1;
}

int isFull(stack *STACK) {
    return STACK->top == MAX_STACK - 1;
}

int isEmpty(stack *STACK) {
    return STACK->top == -1;
}

int Push(stack *STACK, int value) {
    STACK->data[++(STACK->top)] = value;
}

void Pop(stack *STACK) {
    STACK->top--;
}

int peek(stack *STACK) {
    return STACK->data[STACK->top];
}

int Find(stack *STACK, int value) {
    for (int i = 0; i <= STACK->top; i++) {
        if (STACK->data[i] == value) {
            return i; 
        }
    }
    return -1; 
}

void Edit(stack *STACK, int old_value, int new_value) {
    int index = Find(STACK, old_value); 
    if (index == -1) {
        printf("Element not found in the stack\n");
        return;
    }

    STACK->data[index] = new_value; 
    printf("Element %d replaced with %d\n", old_value, new_value);
}

void menu() {
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("4. Find\n");
    printf("5. Edit\n");
    printf("6. Exit\n");
}

int main() {
    stack tumpuk;
    inisialisasi(&tumpuk);

    int choice, value, old_value, new_value, stop = 0;

    while(1) {
        menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if (isFull(&tumpuk)) {
                    printf("Stack is full\n");
                    break;
                }
                printf("Enter value: ");
                scanf("%d", &value);
                Push(&tumpuk, value);
                break;
            case 2:
                if (isEmpty(&tumpuk)) {
                    printf("Stack is empty\n");
                    break;
                }
                Pop(&tumpuk);
                break;
            case 3:
                if (peek(&tumpuk) == -1) {
                    printf("Stack is empty\n");
                    break;
                }
                printf("Top element is %d\n", peek(&tumpuk));
                break;
            case 4:
                if (isEmpty(&tumpuk)) {
                    printf("Stack is empty\n");
                    break;
                }
                printf("Enter the value to find: ");
                scanf("%d", &value);
                int index = Find(&tumpuk, value);
                if (index == -1) {
                    printf("Element not found in the stack\n");
                }
                else {
                    printf("Element found in the stack\n");
                }
                break;
            case 5:
                if (isEmpty(&tumpuk)) {
                    printf("Stack is empty\n");
                    break;
                }
                printf("Enter the value to edit: ");
                scanf("%d", &old_value);
                printf("Enter the new value: ");
                scanf("%d", &new_value);
                Edit(&tumpuk, old_value, new_value);
                break;
            case 6:
                stop = 1;
                break;
            default:
                printf("Invalid choice\n");
        }
        if(stop){
            break;
        }
    }

    return 0;
}
