#include <stdio.h>

void swapNumbers(int *x, int *y, int *z);

int main() {
    int e1, e2, e3;

    scanf("%d %d %d", &e1, &e2, &e3);

    swapNumbers(&e1, &e2, &e3);

    printf("%d %d %d", e1, e2, e3);

    return 0;
}

// Function definition to swap the values of three integer pointers
void swapNumbers(int *x, int *y, int *z) {
    int temp = *x;
    *x = *z;
    *z = *y;
    *y = temp;
}
