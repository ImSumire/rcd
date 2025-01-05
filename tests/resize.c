#include "../src/lib.h"


int main() {
    int* arr = (int*)alloc(sizeof(int) * 8);
    for (int i = 0; i < 8; i++) {
        arr[i] = i;
    }

    printf("Original array: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    arr = resize(arr, sizeof(int) * 16);

    for (int i = 8; i < 16; i++) {
        arr[i] = i;
    }

    printf("Resized array: ");
    for (int i = 0; i < 16; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
