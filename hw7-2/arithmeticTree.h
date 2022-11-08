#pragma once

#include <stdbool.h>

struct ArithmeticTreeElement;
struct ArithmeticTree;
enum Error;

enum Error
addNewWithCurrKnotLink(struct ArithmeticTree **arithmeticTree, struct ArithmeticTreeElement **currElement, bool isLeft);

enum Error assignValueCurr(struct ArithmeticTreeElement **currElement, int value, char operation);

void deleteTree(struct ArithmeticTree *ArithmeticTree);

int treeRes(struct ArithmeticTree *arithmeticTree);

void printTree(struct ArithmeticTree *arithmeticTree);