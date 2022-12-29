#pragma once

#include <stdlib.h>


typedef struct StackElement {
    char value;
    struct StackElement *prev;
} StackElement;

typedef struct {
    StackElement *lastElement;
} StackTail;

int tailValue(StackTail *stack, char *value); //assigns stack last element value to (*value)

StackTail *create(int *result); //creates stack

int isEmpty(StackTail *stack); //checks if stack is empty

int push(StackTail *stack, char element); //adds new element with value=element in stack

int pop(StackTail *stack, char *value); //deletes last element in stack and assigns last element value to variable with address char *value
