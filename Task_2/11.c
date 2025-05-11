11_147.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char data;
    struct node *next;
};

void free_list(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp);
    }
}

int delete_first_occurrence(struct node **head_ptr, char c) {
    struct node *current = *head_ptr;
    struct node *prev = NULL;

    while (current != NULL) {
        if (current->data == c) {
            if (prev == NULL) {
                *head_ptr = current->next;
            } 
            else {
                prev->next = current->next;
            }
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }

    return 0;
}

struct node *copy_list(struct node *head) {
    struct node *current = head;
    struct node *copy_head = NULL;
    struct node **copy_current = &copy_head;

    while (current != NULL) {
        *copy_current = malloc(sizeof(struct node));
        (*copy_current)->data = current->data;
        (*copy_current)->next = NULL;                   
        copy_current = &((*copy_current)->next);
        current = current->next;
    }

    return copy_head;
}

int is_anagram(struct node *w1, struct node *w2) {
    struct node *copy_w1 = w1;
    struct node *copy_w2 = copy_list(w2);

    while (copy_w1 != NULL) {
        char c = copy_w1->data;
        if (!delete_first_occurrence(&copy_w2, c)) {
            free_list(copy_w2);
            return 0;
        }
        copy_w1 = copy_w1->next;
    }

    int result = (copy_w2 == NULL);
    free_list(copy_w2);
    return result;
}

struct node *create_word(char *str) {
    struct node *head = NULL;
    struct node **current = &head;

    for (int i = 0; str[i] != '\0'; i++) {
        *current = malloc(sizeof(struct node));
        (*current)->data = str[i];
        (*current)->next = NULL;
        current = &((*current)->next);
    }

    return head;
}

int main(){
    char word1[100], word2[100];

    printf("Enter the first word: ");
    scanf("%s", word1);
    printf("Enter the second word: ");
    scanf("%s", word2);

    if(strlen(word1) != strlen(word2)){
        printf("The words are not anagrams.\n");
        return 0;
    }

    struct node *w1 = create_word(word1);
    struct node *w2 = create_word(word2);

    if(is_anagram(w1, w2)){
        printf("The words are anagrams.\n");
    } 
    else{
        printf("The words are not anagrams.\n");
    }

    free_list(w1);
    free_list(w2);

    return 0;
}
