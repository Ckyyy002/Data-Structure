#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *add_numbers(struct node *num1, struct node *num2) {
    struct node dummy;
    struct node *tail = &dummy;
    dummy.next = NULL;
    int value1, value2, carry = 0;
    
    while (num1 != NULL || num2 != NULL || carry != 0) {
        if (num1 != NULL) {
            value1 = num1->value;
        } 
        else {
            value1 = 0;
        }
        
        if (num2 != NULL) {
            value2 = num2->value;
        } 
        else {
            value2 = 0;
        }
        
        int total = value1 + value2 + carry;
        carry = total / 10;
        int digit = total % 10;
        
        struct node *new_node = malloc(sizeof(struct node));
        new_node->value = digit;
        new_node->next = NULL;
        
        tail->next = new_node;
        tail = new_node;
        
        if (num1 != NULL) {
            num1 = num1->next;
        }
        if (num2 != NULL) {
            num2 = num2->next;
        }
    }
    
    return dummy.next;
}

struct node *create_list(int num) {
    struct node dummy;
    struct node *tail = &dummy;
    dummy.next = NULL;
    
    if (num == 0) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->value = 0;
        new_node->next = NULL;
        tail->next = new_node;
        tail = new_node;
    } 
    else {
        while (num > 0) {
            int digit = num % 10;
            num /= 10;
            struct node *new_node = malloc(sizeof(struct node));
            new_node->value = digit;
            new_node->next = NULL;
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    return dummy.next;
}

void print(struct node *head) {
    struct node *current = head;
    if (current == NULL) {
        return;
    }
    print(current->next);           
    printf("%d", current->value);
}

void free_list(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        struct node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int x, y;

    printf("Enter the first number: ");
    scanf("%d", &x);
    printf("Enter the second number: ");
    scanf("%d", &y);

    struct node* num1 = create_list(x);
    struct node* num2 = create_list(y);
    struct node* sum = add_numbers(num1, num2);

    printf("Sum of the two numbers: ");
    print(sum);

    free_list(num1);
    free_list(num2);
    free_list(sum);

    return 0;
}
