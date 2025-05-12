#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    char data;
    struct Stack *next;
} Stack;

void push(Stack *stack, char data) {
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    newNode->data = data;
    newNode->next = stack->next;
    stack->next = newNode;
}

void print(Stack *stack) {
    Stack *current = stack->next;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->next = NULL;
    char word[101];
    
    scanf("%s", word);
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u' || word[i] == 'A' || word[i] == 'E' || word[i] == 'I' || word[i] == 'O' || word[i] == 'U') {
            push(stack, word[i]);
        }
        push(stack, word[i]);
    }

    print(stack);
    return 0;
}