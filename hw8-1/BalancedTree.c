#include "BalancedTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum Error {
    noTree,
    memoryAllocationError,
    OK
} Error;

typedef struct Tree {
    int key;
    int height;
    char *value;
    struct Tree *right;
    struct Tree *left;
} Tree;

int height(Tree *tree) {
    if (tree == NULL) {
        return 0;
    }
    return tree->height;
}

int max(int fstNumber, int sndNumber) {
    if (fstNumber > sndNumber) {
        return fstNumber;
    }
    return sndNumber;
}

int knotBalanceCounter(Tree *tree) {
    return height(tree->right) - height(tree->left);
}

void overHeight(Tree *tree) {
    int hLeft = height(tree->left);
    int hRight = height(tree->right);
    tree->height = max(hRight, hLeft) + 1;
}


Tree *RightRotation(Tree *a) {
    Tree *b = a->left;
    a->left = b->right;
    b->right = a;
    overHeight(a);
    overHeight(b);
    return b;
}

Tree *LeftRotation(Tree *a) {
    Tree *b = a->right;
    a->right = b->left;
    b->left = a;
    overHeight(a);
    overHeight(b);
    return b;
}

Tree *balance(Tree *tree) {
    overHeight(tree);
    if (knotBalanceCounter(tree) == 2) {
        if (knotBalanceCounter(tree->right) < 0) {
            tree->right = RightRotation(tree->right);
        }
        return LeftRotation(tree);
    }
    if (knotBalanceCounter(tree) == -2) {
        if (knotBalanceCounter(tree->left) > 0) {
            tree->left = LeftRotation(tree->left);
        }
        return RightRotation(tree);
    }
    return tree;
}

Tree *insert(Tree **tree, int key, char *value, Error *error) {
    if (*tree == NULL) {
        *tree = calloc(1, sizeof(Tree));
        if (*tree == NULL) {
            *error = memoryAllocationError;
            return NULL;
        }
        (*tree)->value = calloc(1, sizeof(value));
        if ((*tree)->value == NULL) {
            *error = memoryAllocationError;
            return NULL;
        }
        strcpy((*tree)->value, value);
        (*tree)->key = key;
        (*tree)->height = 1;
        return *tree;
    }
    if (key < (*tree)->key) {
        (*tree)->left = insert(&((*tree)->left), key, value, error);
    } else if (key > (*tree)->key) {
        (*tree)->right = insert(&((*tree)->right), key, value, error);
    } else {
        free((*tree)->value);
        (*tree)->value = calloc(1, sizeof(value));
        if ((*tree)->value == NULL) {
            *error = memoryAllocationError;
            return NULL;
        }
        strcpy((*tree)->value, value);
        return (*tree);
    }
    return balance(*tree);
}

Tree *searchMin(Tree *tree) {
    if (tree->left != NULL) {
        return searchMin(tree->left);
    }
    return tree;
}

Tree *deleteMin(Tree *tree) {
    if (tree->left == NULL) {
        return tree->right;
    }
    tree->left = deleteMin(tree->left);
    return balance(tree);
}

Tree *delete(Tree **tree, int k, Error *error) {
    if (*tree == NULL) {
        *error = noTree;
        return NULL;
    }
    if (k < (*tree)->key) {
        (*tree)->left = delete(&(*tree)->left, k, error);
    } else if (k > (*tree)->key) {
        (*tree)->right = delete(&(*tree)->right, k, error);
    } else {
        Tree *treeLeft = (*tree)->left;
        Tree *treeRight = (*tree)->right;
        free((*tree)->value);
        free((*tree));
        if (treeRight == NULL) {
            return treeLeft;
        }
        Tree *min = searchMin(treeRight);
        min->right = deleteMin(treeRight);
        min->left = treeLeft;
        return balance(min);
    }
    return balance((*tree));
}

void depthPrint(Tree *treeElement) {
    if (treeElement == NULL) return;
    printf("%d     ", treeElement->key);
    depthPrint(treeElement->right);
    printf("\n");
    depthPrint(treeElement->left);
}

void depthSearch(Tree *treeElement, bool *isFound, int key) {
    if (treeElement == NULL) return;
    if (treeElement->key == key) {
        *isFound = true;
        return;
    } else {
        depthSearch(treeElement->left, isFound, key);
    }
    depthSearch(treeElement->right, isFound, key);
}

Error getValueByKey(Tree *tree, int key, char **value) {
    if (tree == NULL) {
        return noTree;
    }
    bool isFound = false;
    depthSearch(tree, &isFound, key);
    if (!isFound) {
        *value = NULL;
        return OK;
    }
    Tree *curr = tree;
    while (curr->key != key) {
        if (curr->key > key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    *value = calloc(1, sizeof(curr->value));
    if (*value == NULL) {
        return memoryAllocationError;
    }
    strcpy(*value, curr->value);
    return OK;
}

void printTree(Tree *tree) {
    printf("\nYour tree:\n");
    if (tree == NULL) {
        return;
    }
    depthPrint(tree);
}

void deleteTree(Tree **tree) {
    if (*tree == NULL) {
        return;
    }
    deleteTree(&(*tree)->left);
    deleteTree(&(*tree)->right);
    free((*tree)->value);
    free((*tree));
}
