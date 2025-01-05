#pragma once

#include <stdlib.h>

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

