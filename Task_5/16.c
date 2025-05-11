#include <stdio.h>
#define MAX 16

void complete(int *bst, int *arr2, int index, int start, int end) {
    if (start > end || index >= MAX) {
        return;
    }

    int mid = (start + end) / 2;
    bst[index] = arr2[mid];

    complete(bst, arr2, 2 * index, start, mid - 1);       
    complete(bst, arr2, 2 * index + 1, mid + 1, end);     
}

int main() {
    int arr1[] = {34, 23, 45, 46, 37, 78, 90, 2, 40, 20, 87, 53, 12, 15, 91};
    int arr2[15];
    int bst[MAX] = {0}; 

    for (int i = 0; i < 15; i++) {
        arr2[i] = arr1[i];
    }

    for (int i = 0; i < 14; i++) {
        for (int j = i + 1; j <= 14; j++) {
            if (arr2[i] > arr2[j]) {
                int temp = arr2[i];
                arr2[i] = arr2[j];
                arr2[j] = temp;
            }
        }
    }

    complete(bst, arr2, 1, 0, 14);

    for (int i = 1; i <= 15; i++) {
        printf("%d ", bst[i]);
    }

    return 0;
}
