#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct stackarr_t {
    long *_element;
    long _topIndex;
    unsigned int _size;
    unsigned int _capacity;
} StackArray;

void stackArray_init(StackArray *stack, unsigned int stackSize);
bool stackArray_isEmpty(StackArray *stack);
void stackArray_push(StackArray *stack, long value);
void stackArray_pop(StackArray *stack);
long stackArray_top(StackArray *stack);
long stackArray_top2(StackArray *stack);
long to_num(const char *str);
bool digitCheck(char c);

void stackArray_init(StackArray *stack, unsigned int stackSize) {
    stack->_element = (long*)malloc(sizeof(long) * stackSize);
    stack->_size = 0;
    stack->_topIndex = -1;
    stack->_capacity = stackSize;
}

bool stackArray_isEmpty(StackArray *stack) {
    return (stack->_topIndex == -1);
}

void stackArray_push(StackArray *stack, long value) {
    if (stack->_size + 1 <= stack->_capacity) {
        stack->_element[++stack->_topIndex] = value;
        stack->_size++;
    }
}

void stackArray_pop(StackArray *stack) {
    if (!stackArray_isEmpty(stack)) {
        stack->_topIndex--;
        stack->_size--;
    }
}

long stackArray_top(StackArray *stack) {
    if (!stackArray_isEmpty(stack)) {
        return stack->_element[stack->_topIndex];
    }
    return 0;
}

long stackArray_top2(StackArray *stack) {
    if (!stackArray_isEmpty(stack) && stack->_topIndex > 0) {
        int x = stack->_topIndex - 1;
        return stack->_element[x];
    }
    return 0;
}

bool digitCheck(char c) {
    return (c >= '0' && c <= '9');
}

long to_num(const char *str) {
    long num = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        if (digitCheck(str[i])) {
            num = num * 10 + (str[i] - '0');
            i++;
        } 
        else {
            break;
        }
    }

    return num * sign;
}

int main(int argc, char const *argv[]) {
    StackArray myStack;
    stackArray_init(&myStack, 1000);

    char s[1001];
    fgets(s, sizeof(s), stdin);

    char *token = strtok(s, " \n");
    while (token != NULL) {
        if (strcmp(token, "C") == 0) { 
            stackArray_pop(&myStack);
        }
        else if (strcmp(token, "D") == 0) {
            long x = 2 * stackArray_top(&myStack);
            stackArray_push(&myStack, x);
        }
        else if (strcmp(token, "+") == 0) {
            long x = stackArray_top(&myStack) + stackArray_top2(&myStack);
            stackArray_push(&myStack, x);
        }
        else {
            long x = to_num(token);
            stackArray_push(&myStack, x);
        }
        token = strtok(NULL, " \n");
    }

    long result = 0;

    while (!stackArray_isEmpty(&myStack)) {
        result += stackArray_top(&myStack);
        stackArray_pop(&myStack);
    }

    printf("%ld", result);

    return 0;
}