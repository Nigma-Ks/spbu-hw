#pragma once

#include <stdlib.h>


typedef struct StackElement {
    int value;
    struct StackElement *prev;
} StackElement;

typedef struct {
    StackElement *lastElement;
} StackTail;

StackTail *create(int *result); //creates stack

int push(StackTail *stack, int element); //adds new element with value=element in stack

int pop(StackTail *stack, int *value); //deletes last element in stack and assigns last element value to variable with addres int *value
