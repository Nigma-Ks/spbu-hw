#pragma once

#include <stdbool.h>

struct Tree;

enum Error;

struct Tree *RightRotation(struct Tree *a);

struct Tree *LeftRotation(struct Tree *a);

struct Tree *balance(struct Tree *tree);

void printTree(struct Tree *tree);

void depthSearch(struct Tree *treeElement, bool *isFound, int key);

struct Tree *insert(struct Tree **tree, int key, char *value, enum Error *error);

struct Tree *delete(struct Tree **tree, int k, enum Error *error);

void deleteTree(struct Tree **tree);

enum Error getValueByKey(struct Tree *tree, int key, char **value);