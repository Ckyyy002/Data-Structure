#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head, *tail;
} List;

void init(List *list) {
    list->head = NULL;
    list->tail = NULL;
}

void push(List *list, char value){
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
        
    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        Node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void pop(List *list){
    Node *nextNode = list->head->next;
    Node *currNode = list->head;

    if (currNode->next == NULL) {
        free(currNode);
        list->head = NULL;
        return;
    }

    while (nextNode->next != NULL) {
        currNode = nextNode;
        nextNode = nextNode->next;
    }
    currNode->next = NULL;
    free(nextNode);
}

void print(List *list) {
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    List *list = (List *)malloc(sizeof(List));
    init(list);

    while (1){
        char cmd[10], input;
        scanf("%s", cmd);

        if(strcmp(cmd, "WRITE") == 0){
            scanf(" %c", &input);
            push(list, input);
        }
        else if(strcmp(cmd, "BACKSPACE") == 0){
            pop(list);
        }
        else{
            print(list);
            break;
        }
    }
    return 0;
}