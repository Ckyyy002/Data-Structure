10_147.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float jumps[3];
    int attempt;
    float best_jump;
} athlete;

void update_best_jump(athlete *jumper) {
    jumper->best_jump = 0; 
    for (int i = 0; i < jumper->attempt; i++) { 
        if (jumper->jumps[i] > jumper->best_jump) {  
            jumper->best_jump = jumper->jumps[i];  
        }
    }
}

void sort_jumpers(athlete jumper[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jumper[j].best_jump < jumper[j + 1].best_jump) {
                athlete temp = jumper[j];
                jumper[j] = jumper[j + 1];
                jumper[j + 1] = temp;
            }
        }
    }
}

int main() {
    FILE *file = fopen("jumpers.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    athlete jumper[8];
    int player = 0;
    char name[50];
    float distance;

    while (fscanf(file, " %s %f", name, &distance) == 2) {
        int found = 0;
        for (int i = 0; i < player; i++) {
            if (strcmp(jumper[i].name, name) == 0) {
                if (jumper[i].attempt < 3) {
                    jumper[i].jumps[jumper[i].attempt++] = distance;
                    update_best_jump(&jumper[i]);
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            athlete nw;
            strcpy(nw.name, name);
            nw.jumps[0] = distance;
            nw.attempt = 1;
            update_best_jump(&nw);
            jumper[player++] = nw;
        }
    }

    fclose(file);

    sort_jumpers(jumper, player);

    printf("Best jumps in order:\n");
    for (int i = 0; i < player; i++) {
        printf("%s %.2f\n", jumper[i].name, jumper[i].best_jump);
    }

    return 0;
}
