#include "../src/lib.h"


int main() {
    for (int i = 0; i < 65536; i++)
        alloc(sizeof(int));
}
