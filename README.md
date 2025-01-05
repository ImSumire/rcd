# Reference Counting Destructor

## Overview
The **Reference Counting Destructor** library provides a simple way to not manage memory in C. It uses reference counting (just the pointer counting part) to calls the free function at the end of the program. It uses custom signal handlers to prevent leaks at crashes.

## Usage
```c
#include "./src/lib.h"


int main() {
    // Allocation
    for (int i = 0; i < 65536; i++)
        alloc(sizeof(int));
    
    // Droping
    int* ptr = (int*)alloc(sizeof(int));
    drop(ptr);

    int* ptr2 = (int*)alloc(sizeof(int));

    // Copying
    int* x = (int*)alloc(sizeof(int));
    *x = 42;

    int* y = (int*)copy(x, sizeof(int));

    // Resizing
    int* arr = (int*)alloc(sizeof(int) * 8);
    arr = resize(arr, sizeof(int) * 16);
}
```
