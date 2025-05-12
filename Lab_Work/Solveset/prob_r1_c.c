#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct snode_t {
    long long data;
    struct snode_t *next;
} SListNode;

typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

void slist_init(SinglyList *list) {
    list->_head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushFront(SinglyList *list, long long value) {
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;

        if (slist_isEmpty(list)) {
            newNode->next = NULL;
        }
        else {
            newNode->next = list->_head;
        }
        list->_head = newNode;
    }
}

void print(SinglyList *list) {
    SListNode *current = list->_head;
    while (current != NULL) {
        printf("%lld ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(){
    SinglyList myList;
    slist_init(&myList);

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        long long value;
        scanf("%lld", &value);
        slist_pushFront(&myList, value);
    }

    print(&myList);
}