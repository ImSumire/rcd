#pragma once

#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>


#define DEBUG_BANNER "\x1b[37;44m DEBUG \x1b[0m "
#define VALID_BANNER "\x1b[37;42m VALID \x1b[0m "
#define HINT_BANNER "\x1b[37;46m HINT \x1b[0m "

#define WARN_BANNER "\x1b[37;43m WARN \x1b[0m "
#define ERROR_BANNER "\x1b[37;41m ERROR \x1b[0m "

/**
 * @struct AvlNode
 * @brief A node in the AVL tree.
 *
 * Each node has a key, left and right child pointers, and a height.
 * Size: 32 bytes
 */
typedef struct AvlNode {
    void* key;
    struct AvlNode* left;
    struct AvlNode* right;
    int height;
} AvlNode;

/**
 * @struct AvlTree
 * @brief The AVL tree data structure.
 *
 * The AVL tree is represented by a single node, the root.
 * Size: 8 bytes
 */
typedef struct {
    AvlNode* root;
} AvlTree;

/**
 * @brief Creates a new AVL tree.
 *
 * @return A pointer to the new AVL tree.
 */
AvlTree* avl_new() {
    AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
    tree->root = NULL;
    return tree;
}

/**
 * @brief Drops an AVL node and all its children.
 *
 * @param node The node to drop.
 */
void avlnode_drop(AvlNode* node) {
    if (node) {
        avlnode_drop(node->left);
        avlnode_drop(node->right);
        free(node);
    }
}

/**
 * @brief Drops an AVL tree.
 *
 * @param tree The tree to drop.
 */
void avl_drop(AvlTree* tree) {
    avlnode_drop(tree->root);
    free(tree);
}

/**
 * @brief Gets the height of an AVL node. O(1)
 *
 * @param node The node to get the height of.
 * @return The height of the node.
 */
int avlnode_get_height(AvlNode* node) {
    return node ?
        node->height : 0;
}

/**
 * @brief Gets the balance factor of an AVL node. O(1)
 *
 * @param node The node to get the balance factor of.
 * @return The balance factor of the node.
 */
int avlnode_get_balance(AvlNode* node) {
    return node ?
        avlnode_get_height(node->left) - avlnode_get_height(node->right) : 0;
}

/**
 * @brief Updates the height of an AVL node. O(1)
 *
 * @param node The node to update the height of.
 */
void avlnode_update_height(AvlNode* node) {
    node->height =
        1 +
        (avlnode_get_height(node->left) > avlnode_get_height(node->right) ?
            avlnode_get_height(node->left) : avlnode_get_height(node->right)
        );
}

/**
 * @brief Rotates an AVL node to the left. O(1)
 *
 * @param node The node to rotate.
 * @return The new root node after rotation.
 */
AvlNode* avlnode_rotate_left(AvlNode* node) {
    AvlNode* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    avlnode_update_height(node);
    avlnode_update_height(temp);
    return temp;
}

/**
 * @brief Rotates an AVL node to the right. O(1)
 *
 * @param node The node to rotate.
 * @return The new root node after rotation.
 */
AvlNode* avlnode_rotate_right(AvlNode* node) {
    AvlNode* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    avlnode_update_height(node);
    avlnode_update_height(temp);
    return temp;
}

/**
 * @brief Rebalances an AVL node. 0(1)
 *
 * @param node The node to rebalance.
 * @return The new root node after rebalancing.
 */
AvlNode* avlnode_rebalance(AvlNode* node) {
    avlnode_update_height(node);
    int balance = avlnode_get_balance(node);
    if (balance > 1) {
        if (
            avlnode_get_height(node->left->left) >=
            avlnode_get_height(node->left->right)
        ) {
            return avlnode_rotate_right(node);
        }
        else {
            node->left = avlnode_rotate_left(node->left);
            return avlnode_rotate_right(node);
        }
    }
    if (balance < -1) {
        if (
            avlnode_get_height(node->right->right) >=
            avlnode_get_height(node->right->left)
        ) {
            return avlnode_rotate_left(node);
        }
        else {
            node->right = avlnode_rotate_right(node->right);
            return avlnode_rotate_left(node);
        }
    }
    return node;
}

/**
 * @brief Inserts a new key into the AVL tree. O(log2(n))
 *
 * @param node The node to insert the key into.
 * @param key The key to insert.
 */
void avlnode_insert(AvlNode** node, void* key) {
    if (*node == NULL) {
        *node = (AvlNode*)malloc(sizeof(AvlNode));
        (*node)->key = key;
        (*node)->left = NULL;
        (*node)->right = NULL;
        (*node)->height = 1;
    }
    else if (key < (*node)->key) {
        avlnode_insert(&((*node)->left), key);
    }
    else if (key > (*node)->key) {
        avlnode_insert(&((*node)->right), key);
    }

    *node = avlnode_rebalance(*node);
}

/**
 * @brief Inserts a new key into the AVL tree. O(log2(n))
 *
 * @param tree The tree to insert the key into.
 * @param key The key to insert.
 */
void avl_insert(AvlTree* tree, void* key) {
    avlnode_insert(&(tree->root), key);
}

/**
 * @brief Removes a key from the AVL tree. O(log2(n))
 *
 * @param node The node to remove the key from.
 * @param key The key to remove.
 */
void avlnode_remove(AvlNode** node, void* key) {
    if (*node == NULL)
        return;
    
    if (key < (*node)->key) {
        avlnode_remove(&((*node)->left), key);
    }
    else if (key > (*node)->key) {
        avlnode_remove(&((*node)->right), key);
    }
    else {
        if ((*node)->left == NULL) {
            AvlNode* temp = (*node)->right;
            free(*node);
            *node = temp;
        }
        else if ((*node)->right == NULL) {
            AvlNode* temp = (*node)->left;
            free(*node);
            *node = temp;
        }
        else {
            AvlNode* temp = (*node)->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            (*node)->key = temp->key;
            avlnode_remove(&((*node)->right), temp->key);
        }
    }

    if (*node != NULL) {
        *node = avlnode_rebalance(*node);
    }
}

/**
 * @brief Removes a key from the AVL tree. O(log2(n))
 *
 * @param tree The tree to remove the key from.
 * @param key The key to remove.
 */
void avl_remove(AvlTree* tree, void* key) {
    avlnode_remove(&(tree->root), key);
}

/**
 * @brief Iterates over the keys in the AVL tree. O(n)
 *
 * @param node The node to iterate over.
 * @param func The function to call for each key.
 */
void avlnode_iter(AvlNode* node, void (*func)(void*)) {
    if (node) {
        avlnode_iter(node->left, func);
        func(node->key);
        avlnode_iter(node->right, func);
    }
}

/**
 * @brief Iterates over the keys in the AVL tree, calls a function for each key, and then deletes the node. O(n)
 *
 * @param node The node to iterate over.
 * @param func The function to call for each key.
 */
void avlnode_iter_destroy(AvlNode* node, void (*func)(void*)) {
    if (node) {
        avlnode_iter_destroy(node->left, func);
        avlnode_iter_destroy(node->right, func);
        func(node->key);
        free(node);
    }
}

/**
 * @brief Iterates over the keys in the AVL tree. O(n)
 *
 * @param tree The tree to iterate over.
 * @param func The function to call for each key.
 */
void avl_iter(AvlTree* tree, void (*func)(void*)) {
    avlnode_iter(tree->root, func);
}

/**
 * @brief Iterates over the keys in the AVL tree, calls a function for each key, and then deletes the node. O(n)
 *
 * @param tree The tree to iterate over.
 * @param func The function to call for each key.
 */
void avl_iter_destroy(AvlTree* tree, void (*func)(void*)) {
    avlnode_iter_destroy(tree->root, func);
    free(tree);
}


void __display_signal_help() {
    printf(
        "\n" HINT_BANNER "Online docs for signal errors:\n\
 \x1b[2m·\x1b[0m Wikipedia: \x1b[0;4;34mhttps://en.wikipedia.org/wiki/Signal_(IPC)#POSIX_signals\x1b[0m\n\
 \x1b[2m·\x1b[0m GNU: \x1b[0;4;34mhttps://www.gnu.org/software/libc/manual/html_node/Standard-Signals.html\x1b[0m\n\
 \x1b[2m·\x1b[0m Linux Man: \x1b[0;4;34mhttps://man7.org/linux/man-pages/man7/signal.7.html\x1b[0m\n"
    );
}

// SIGHUP: 1	Hangup
void sighup_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mHangup signal received. \x1b[30mThis can occur when the terminal\nthat started the process is closed or disconnected.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGINT: 2	Interactive attention signal.
void sigint_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mInteractive attention  signal received.  \x1b[30mThis can occur when\nthe user presses Ctrl+C in the terminal where the process is\nrunning.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGQUIT: 3	Quit.
void sigquit_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mQuit signal received. \x1b[30mThis can occur when the user presses\nCtrl+\\ in the terminal where the process is running.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGILL: 4	Illegal instruction.
void sigill_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mIllegal instruction signal received. \x1b[30mThis can occur when the\nprocess  attempts  to  execute    an  invalid   or undefined\ninstruction.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGTRAP: 5	Trace/breakpoint trap.
void sigtrap_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mTrace/breakpoint trap signal received. \x1b[30mThis can occur when\nthe process hits a breakpoint set by a debugger.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGABRT: 6	Abnormal termination.
void sigabrt_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mAbnormal termination signal received. \x1b[30mThis can occur when\nthe process  is terminated  abnormally,  such as  when it\nencounters an unrecoverable error.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGFPE: 8	Erroneous arithmetic operation.
void sigfpe_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mErroneous  arithmetic operation  signal  received. \x1b[30mThis can\noccur  when the process  attempts  to  perform   an invalid\narithmetic operation.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGKILL: 9	Killed.
// The signals SIGKILL and SIGSTOP cannot be caught, blocked, or ignored.
// void sigkill_handler(int signal);

// SIGSEGV: 11	Invalid access to storage.
void sigsegv_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mInvalid access  to storage  signal  received. \x1b[30mThis can occur\nwhen the process attempts to access  memory  that it  is not\nallowed to access.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGPIPE: 13	Broken pipe.
void sigpipe_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mBroken pipe signal received. \x1b[30mThis can occur when the process\nwrites to a pipe that has been closed by the other end.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGALRM: 14	Alarm clock.
void sigalrm_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mAlarm clock signal received. \x1b[30mThis can occur when a timer set\nby the process expires.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGTERM: 15	Termination request.
void sigterm_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mTermination request signal received. \x1b[30mThis can occur when the\nprocess is requested to terminate cleanly.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}


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
