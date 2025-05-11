#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

int isOperator(char c) {
    if (c == '^') {
        return 3;
    }
    else if (c == '/' || c == '*') {
        return 2;
    }
    else if (c == '+' || c == '-') {
        return 1;
    }
    else {
        return -1;
    }
}

void postfix(char* infix) {
    int len = strlen(infix), j = 0, top = -1;
    char result[len + 1], stack[len];

    for (int i = 0; i < len; i++) {
        char c = infix[i];
        if (isOperand(c)) {
            result[j++] = c;
        }
        else if (c == '(') {
            stack[++top] = '(';
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                result[j++] = stack[top--];
            }
            top--; 
        }
        else {
            while (top != -1 && (isOperator(c) < isOperator(stack[top]) || isOperator(c) == isOperator(stack[top]))) {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top != -1) {
        result[j++] = stack[top--];
    }

    result[j] = '\0';
    printf("%s\n", result);
}

int main() {
    char infix[100];
    scanf("%s", infix);
    postfix(infix);
    return 0;
}
