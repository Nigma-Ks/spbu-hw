#pragma once

#include <stdlib.h>


typedef struct StackElement {
    int value;
    struct StackElement *prev;
} StackElement;

typedef struct {
    StackElement *lastElement;
} StackTail;

StackTail *create(int *result);

int push(StackTail *stack, int element);

int pop(StackTail *stack, int *value);
