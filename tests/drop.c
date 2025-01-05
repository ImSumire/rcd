#include "../src/lib.h"


int main() {
    int* ptr = (int*)alloc(sizeof(int));

    int* ptr2 = (int*)alloc(sizeof(int));
    drop(ptr2);
}
