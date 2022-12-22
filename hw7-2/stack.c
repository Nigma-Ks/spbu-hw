#include "stack.h"
#include "arithmeticTree.h"

typedef struct StackElement {
    struct ArithmeticTreeElement*treeElement;
    struct StackElement *prev;
} StackElement;

typedef struct StackTail{
    StackElement *lastElement;
} StackTail;

StackTail *create(int *result) {
    StackTail *pStackTail = calloc(1, sizeof(StackTail));
    if (pStackTail == NULL) *result = 2;
    return pStackTail;
}

int push(StackTail *stack, struct ArithmeticTreeElement*treeElement) {
    if (stack == NULL) {
        return 2;
    }
    StackElement *newStackElement = calloc(1, sizeof(StackElement));
    if (newStackElement == NULL) {
        return 1;
    }
    newStackElement->prev = stack->lastElement;
    newStackElement->treeElement = treeElement;
    stack->lastElement = newStackElement;
    return 0;
}

int isEmpty(StackTail *stack) {
    if (stack == NULL) {
        return 2;
    }
    return stack->lastElement == NULL;
}

int tailValue(StackTail *stack, struct ArithmeticTreeElement**treeElement) {
    if (stack == NULL || *treeElement == NULL || isEmpty(stack)) {
        return 2;
    }
    *treeElement = stack->lastElement->treeElement;
    return 0;
}

int lenStack(StackTail *stack, size_t *len) {
    *len = 0;
    StackElement *curr = stack->lastElement;
    while (curr != NULL) {
        ++(*len);
        curr = curr->prev;
    }
    return 0;
}

int pop(StackTail *stack, struct ArithmeticTreeElement**treeElement) {
    if (stack == NULL || *treeElement == NULL || isEmpty(stack)) {
        return 2;
    }
    *treeElement= stack->lastElement->treeElement;
    StackElement *lastElementMemory = stack->lastElement;
    stack->lastElement = stack->lastElement->prev;
    free(lastElementMemory);
    return 0;
}