#include "stack.h"


StackTail *create(int *result) {
    StackTail *pStackTail = calloc(1, sizeof(StackTail));
    if (pStackTail == NULL) *result = 2;
    return pStackTail;
}

int push(StackTail *stack, char element) {
    if (stack == NULL) {
        return 2;
    }
    StackElement *newStackElement = calloc(1, sizeof(StackElement));
    if (newStackElement == NULL) {
        return 1;
    }
    newStackElement->prev = stack->lastElement;
    newStackElement->value = element;
    stack->lastElement = newStackElement;
    return 0;
}

int isEmpty(StackTail *stack) {
    if (stack == NULL) {
        return 2;
    }
    return stack->lastElement == NULL;
}

int tailValue(StackTail *stack, char *value) {
    if (stack == NULL || value == NULL || isEmpty(stack)) {
        return 2;
    }
    *value = stack->lastElement->value;
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

int pop(StackTail *stack, char *value) {
    if (stack == NULL || value == NULL || isEmpty(stack)) {
        return 2;
    }
    *value = stack->lastElement->value;
    StackElement *lastElementMemory = stack->lastElement;
    stack->lastElement = stack->lastElement->prev;
    free(lastElementMemory);
    return 0;
}

