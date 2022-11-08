#pragma once

#include "arithmeticTree.h"
#include <stdlib.h>


struct StackElement;

struct StackTail;

struct StackTail *create(int *result); //creates stack

int
push(struct StackTail *stack, struct ArithmeticTreeElement *treeElement); //adds new element with value=element in stack

int isEmpty(struct StackTail *stack);

int pop(struct StackTail *stack,
        struct ArithmeticTreeElement **treeElement); //deletes last element in stack and assigns last element value to variable with address int *value