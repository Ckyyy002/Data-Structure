#include <stdio.h>

void order(int *bst, int i, int n) {
    if (i > n) {
        return;
    }

    order(bst, 2 * i, n);
    order(bst, 2 * i + 1, n);
    printf("%d ", *(bst + i));
}

int main() {
    int bst[14] = {0, 39, 21, 64, 18, 30, 56, 73, 13, 26, 47, 61, 75, 35};
    order(bst, 1, 13);
    return 0;
}
