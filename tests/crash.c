#include "../src/lib.h"


int main() {
    int* ptr = (int*)alloc(sizeof(int));

    int* crasher = NULL;
    *crasher = 0;
}
