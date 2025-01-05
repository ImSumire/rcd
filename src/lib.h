#pragma once

#include <string.h>

#include "./avl.h"
#include "./signals.h"

static AvlTree* gc;

// Run at the start of the program
void __attribute__((constructor)) startup() {
    signal(SIGHUP, sighup_handler);
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    signal(SIGILL, sigill_handler);
    signal(SIGTRAP, sigtrap_handler);
    signal(SIGABRT, sigabrt_handler);
    signal(SIGFPE, sigfpe_handler);
    signal(SIGSEGV, sigsegv_handler);
    signal(SIGPIPE, sigpipe_handler);
    signal(SIGALRM, sigalrm_handler);
    signal(SIGTERM, sigterm_handler);

    gc = avl_new();
}

// Run at exit() or main return
void __attribute__((destructor)) quit() {
    avl_iter_destroy(gc, free);
}

// Memory management with Reference Counting Destructor
void* alloc(size_t size) {
    void* ptr = malloc(size);
    avl_insert(gc, ptr);
    return ptr;
}

void drop(void* ptr) {
    avl_remove(gc, ptr);
    free(ptr);
}

// [!] Produce invalid reads
void* copy(void* ptr, size_t size) {
    if (ptr == NULL)
        alloc(size);

    void* new_ptr = alloc(size);
    memcpy(new_ptr, ptr, size);

    return new_ptr;
}

// [!] Produce invalid reads
void* resize(void* ptr, size_t new_size) {
    void* new_ptr = copy(ptr, new_size);
    drop(ptr);

    return new_ptr;
}
