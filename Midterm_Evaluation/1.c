#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int x;
    int y;
} titik;

typedef struct {
    titik data[MAX_SIZE];
    int top;
} stack;

void initialize(stack *s) {
    s->top = -1;
}

int isempty(stack *s) {
    return s->top == -1;
}

void push(stack *s, titik p) {
    s->data[++(s->top)] = p;
}

titik pop(stack *s) {
    return s->data[(s->top)--];
}

int main() {
    stack koordinat;
    titik sekarang = {0, 0};
    initialize(&koordinat);

    char cmd[100];
    printf("Masukkan perintah gerakan: ");
    scanf("%s", cmd);
    
    for (int i = 0; i < strlen(cmd); i++) {
        char c = cmd[i];

        switch (c) {
            case 'U':
                push(&koordinat, sekarang);
                sekarang.y += 1;
                break;
            case 'D':
                push(&koordinat, sekarang);
                sekarang.y -= 1;
                break;
            case 'L':
                push(&koordinat, sekarang);
                sekarang.x -= 1;
                break;
            case 'R':
                push(&koordinat, sekarang);
                sekarang.x += 1;
                break;
            default:
                if (!isempty(&koordinat)) {
                    sekarang = pop(&koordinat);
                }
        }
    }
    
    printf("(%d, %d)\n", sekarang.x, sekarang.y);
    
    return 0;
}
