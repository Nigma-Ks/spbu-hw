#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct ArithmeticTreeElement {
    char operation;
    int value;
    struct ArithmeticTreeElement *right;
    struct ArithmeticTreeElement *left;
} ArithmeticTreeElement;

typedef struct ArithmeticTree {
    ArithmeticTreeElement *root;
} ArithmeticTree;

typedef enum Error {
    noTree,
    noElement,
    memoryAllocationError,
    OK
} Error;

Error addNewWithCurrKnotLink(ArithmeticTree **arithmeticTree, ArithmeticTreeElement **currElement, bool isLeft) {
    if (*arithmeticTree == NULL) {
        *arithmeticTree = calloc(1, sizeof(ArithmeticTree));
        if (*arithmeticTree == NULL) {
            return memoryAllocationError;
        }
        (*arithmeticTree)->root = calloc(1, sizeof(ArithmeticTreeElement));
        if ((*arithmeticTree)->root == NULL) {
            return memoryAllocationError;
        }
        *currElement = (*arithmeticTree)->root;
        return OK;
    }
    if (isLeft) {
        (*currElement)->left = calloc(1, sizeof(ArithmeticTreeElement));;
        if ((*currElement)->left == NULL) {
            return memoryAllocationError;
        }
        *currElement = (*currElement)->left;
        return OK;
    }
    (*currElement)->right = calloc(1, sizeof(ArithmeticTreeElement));
    if ((*currElement)->right == NULL) {
        return memoryAllocationError;
    }
    *currElement = (*currElement)->right;
    return OK;
}

Error assignValueCurr(ArithmeticTreeElement **currElement, int value, char operation) {
    if (*currElement == NULL) {
        return noElement;
    }
    if (operation != '\0') {
        (*currElement)->operation = operation;
        return OK;
    }
    (*currElement)->value = value;
    return OK;
}

void deleteTreeDepth(ArithmeticTreeElement *arithmeticTreeElement) {
    if (arithmeticTreeElement == NULL) return;
    deleteTreeDepth(arithmeticTreeElement->left);
    deleteTreeDepth(arithmeticTreeElement->right);
    free(arithmeticTreeElement);
}

void deleteTree(ArithmeticTree *ArithmeticTree) {
    if (ArithmeticTree == NULL) {
        return;
    }
    if (ArithmeticTree->root == NULL) {
        free(ArithmeticTree);
        return;
    }
    deleteTreeDepth(ArithmeticTree->root);
    free(ArithmeticTree);
}

int treeResult(ArithmeticTreeElement *arithmeticTreeElement) {
    char operation = arithmeticTreeElement->operation;
    if (operation != '\0') {
        if (operation == '*') {
            return treeResult(arithmeticTreeElement->right) * treeResult(arithmeticTreeElement->left);
        } else if (operation == '/') {
            return (int) treeResult(arithmeticTreeElement->left) / treeResult(arithmeticTreeElement->right);
        } else if (operation == '+') {
            return treeResult(arithmeticTreeElement->right) + treeResult(arithmeticTreeElement->left);
        } else {
            return treeResult(arithmeticTreeElement->left) - treeResult(arithmeticTreeElement->right);
        }
    }
    return arithmeticTreeElement->value;
}

int treeRes(ArithmeticTree *arithmeticTree) {
    return treeResult(arithmeticTree->root);
}

void depthPrint(ArithmeticTreeElement *dictionaryElement) {
    if (dictionaryElement == NULL) return;
    if (dictionaryElement->operation == '\0') {
        printf("%d ", dictionaryElement->value);
    } else {
        printf("%c", dictionaryElement->operation);
    }
    depthPrint(dictionaryElement->right);
    depthPrint(dictionaryElement->left);
}

void printTree(ArithmeticTree *arithmeticTree) {
    depthPrint(arithmeticTree->root);
    printf("\n");
}