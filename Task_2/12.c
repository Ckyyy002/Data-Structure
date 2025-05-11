#include <stdio.h>
#include <stdlib.h>

struct node {
    int number;
    struct node *next;
};

int main() {
    int n, m;
    printf("Enter number of children and number of the count: ");
    scanf("%d %d", &n, &m);

    if (n <= 0 || m <= 0) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n == 1) {
        printf("Winner: 1\n");
        return 0;
    }

    struct node *head = NULL;
    struct node *tail = NULL;

    for (int i = 1; i <= n; i++) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->number = i;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } 
        else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    tail->next = head;

    struct node *current = head;
    struct node *point = tail; 

    while (current->next != current) { 
        for (int i = 0; i < m - 1; i++) {
            point = current;
            current = current->next;        
        }

        point->next = current->next;
        free(current);
        current = point->next;
    }

    printf("Winner: %d\n", current->number);
    free(current); 

    return 0;
}
