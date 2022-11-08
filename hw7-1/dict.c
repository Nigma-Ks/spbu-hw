#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dict.h"

typedef enum Error {
    noDict,
    memoryAllocationError,
    OK
} Error;

typedef struct DictionaryElement {
    int key;
    char *value;
    struct DictionaryElement *right;
    struct DictionaryElement *left;
} DictionaryElement;

typedef struct Dictionary {
    DictionaryElement *root;
} Dictionary;

void depthPrint(DictionaryElement *dictionaryElement) {
    if (dictionaryElement == NULL) return;
    printf("%s     ", dictionaryElement->value);
    depthPrint(dictionaryElement->right);
    printf("\n");
    depthPrint(dictionaryElement->left);
}

void depthSearch(DictionaryElement *dictionaryElement, bool *isFound, int key) {
    if (dictionaryElement == NULL) return;
    if (dictionaryElement->key == key) {
        *isFound = true;
        return;
    } else {
        depthSearch(dictionaryElement->left, isFound, key);
    }
    depthSearch(dictionaryElement->right, isFound, key);
}

Dictionary *create() {
    Dictionary *dictionary = calloc(1, sizeof(Dictionary));
    return dictionary;
}

bool isKeyInDict(Dictionary *dictionary, int key) {
    bool isFound = false;
    depthSearch(dictionary->root, &isFound, key);
    return isFound;
}

Error getValueByKey(Dictionary *dictionary, int key, char **value) {
    if (dictionary == NULL) {
        return noDict;
    }
    bool isFound = false;
    depthSearch(dictionary->root, &isFound, key);
    if (!isFound) {
        value = NULL;
        return OK;
    }
    DictionaryElement *curr = dictionary->root;
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

Error add(Dictionary *dictionary, int key, const char *value) {
    if (dictionary == NULL) {
        return noDict;
    }
    if (dictionary->root == NULL) {
        dictionary->root = calloc(1, sizeof(DictionaryElement));
        if (dictionary->root == NULL) {
            return memoryAllocationError;
        }
        dictionary->root->value = calloc(1, sizeof(value));
        if (dictionary->root->value == NULL) {
            return memoryAllocationError;
        }
        dictionary->root->key = key;
        strcpy(dictionary->root->value, value);
        return OK;
    }
    DictionaryElement *curr = dictionary->root;
    DictionaryElement *preCurr = NULL;
    bool rightWay = true; //right or left
    while (curr != NULL) {
        preCurr = curr;
        if (curr->key == key) {
            free(curr->value);
            curr->value = calloc(1, sizeof(value));
            if (curr->value == NULL) {
                return memoryAllocationError;
            }
            strcpy(curr->value, value);
            return OK;
        } else if (curr->key > key) {
            curr = curr->left;
            rightWay = false;
        } else {
            curr = curr->right;
            rightWay = true;
        }
    }
    if (rightWay) {
        preCurr->right = calloc(1, sizeof(DictionaryElement));
        if (preCurr->right == NULL) {
            return memoryAllocationError;
        }
        preCurr->right->value = calloc(1, sizeof(value));
        if (preCurr->right->value == NULL) {
            return memoryAllocationError;
        }
        strcpy(preCurr->right->value, value);
        preCurr->right->key = key;
        return OK;
    }
    preCurr->left = calloc(1, sizeof(DictionaryElement));
    if (preCurr->left == NULL) {
        return memoryAllocationError;
    }
    preCurr->left->value = calloc(1, sizeof(value));
    if (preCurr->left->value == NULL) {
        return memoryAllocationError;
    }
    strcpy(preCurr->left->value, value);
    preCurr->left->key = key;
    return OK;
}

Error delete(Dictionary *dictionary, int key) {
    if (dictionary == NULL) {
        return noDict;
    }
    bool isFound = false;
    depthSearch(dictionary->root, &isFound, key);
    if (!isFound) {
        return OK;
    }
    DictionaryElement *elementForDelete = dictionary->root;
    DictionaryElement *prevElementForDelete = NULL;
    bool rightWay = true; //right or left
    while (elementForDelete->key != key) {
        prevElementForDelete = elementForDelete;
        if (elementForDelete->key > key) {
            elementForDelete = elementForDelete->left;
            rightWay = false;
        } else {
            elementForDelete = elementForDelete->right;
            rightWay = true;
        }
    }
    if (elementForDelete->right == NULL && elementForDelete->left == NULL) {
        if (dictionary->root == elementForDelete) {
            free(elementForDelete);
            dictionary->root = NULL;
            return OK;
        }
        if (rightWay) {
            prevElementForDelete->right = NULL;
        } else {
            prevElementForDelete->left = NULL;
        }
        free(elementForDelete);
        return OK;
    }
    if (elementForDelete->left == NULL) {
        if (rightWay) {
            prevElementForDelete->right = elementForDelete->right;
        } else {
            prevElementForDelete->left = elementForDelete->right;
        }
        free(elementForDelete);
        return OK;
    }
    DictionaryElement *elementForChangeWithDelete = elementForDelete;
    prevElementForDelete = elementForDelete;
    elementForDelete = elementForDelete->left;
    rightWay = false;
    while (elementForDelete->right != NULL) {
        prevElementForDelete = elementForDelete;
        elementForDelete = elementForDelete->right;
        rightWay = true;
    }
    elementForChangeWithDelete->key = elementForDelete->key;
    free(elementForChangeWithDelete->value);
    elementForChangeWithDelete->value = calloc(1, sizeof(elementForDelete->value));
    if (elementForChangeWithDelete->value == NULL) {
        return memoryAllocationError;
    }
    strcpy(elementForChangeWithDelete->value, elementForDelete->value);
    if (rightWay) {
        prevElementForDelete->right = elementForDelete->left;
    } else {
        prevElementForDelete->left = elementForDelete->left;
    }
    free(elementForDelete->value);
    free(elementForDelete);
    return OK;
}

void printDict(Dictionary *dictionary) {
    printf("\nYour dictionary:\n");
    depthPrint(dictionary->root);
}

void deleteDictDepth(DictionaryElement *dictionaryElement) {
    if (dictionaryElement == NULL) return;
    deleteDictDepth(dictionaryElement->left);
    deleteDictDepth(dictionaryElement->right);
    free(dictionaryElement->value);
    free(dictionaryElement);
}

void deleteDict(Dictionary *dictionary) {
    if (dictionary == NULL) {
        return;
    }
    if (dictionary->root == NULL) {
        free(dictionary);
        return;
    }
    deleteDictDepth(dictionary->root);
    free(dictionary);
}