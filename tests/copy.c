#include <assert.h>

#include "../src/lib.h"


int main() {
    int* x = (int*)alloc(sizeof(int));
    *x = 42;

    int* y = (int*)copy(x, sizeof(int));
    printf("y: %d\n", *y);
    assert(*y == 42);
}
