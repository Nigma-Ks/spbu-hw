#include <stdio.h>
#include <stdlib.h>
#include "BalancedTree.h"

typedef enum Error {
    noTree,
    memoryAllocationError,
    OK
} Error;

void showMenu() {
    printf("\nyou can enter this commands to:\n"
           "0 - stop program\n"
           "1 - add new value by defined key\n"
           "2 - delete key with value\n"
           "3 - get value by key\n"
           "4 - check if entered key exist\n"
           "5 - print tree\n");
}

int main() {
    struct Tree *tree = NULL;
    Error error = OK;
    printf("This program creates tree, then");
    showMenu();
    int choice = 0;
    printf("Enter command: ");
    scanf_s("%d", &choice);
    while (choice != 0) {
        while (choice < 0 || choice > 5) {
            printf("\nWrong choice\n");
            showMenu();
            printf("Enter command: ");
            scanf_s("%d", &choice);
        }
        if (choice == 1) {
            int key = 0;
            int lenValue = 0;
            printf("Enter key: ");
            scanf_s("%d", &key);
            printf("Enter amount of chars in value: ");
            scanf_s("%d", &lenValue);
            char *value = calloc(lenValue, sizeof(char));
            printf("Enter value: ");
            scanf_s("%s", value);
            tree = insert(&tree, key, value, &error);
        } else if (choice == 2) {
            int key = 0;
            printf("Enter key: ");
            scanf_s("%d", &key);
            tree = delete(&tree, key, &error);
        } else if (choice == 3) {
            int key = 0;
            printf("Enter key: ");
            scanf_s("%d", &key);
            char *value = "\0";
            getValueByKey(tree, key, &value);
            printf("Value by entered key: %s", value);
        } else if (choice == 4) {
            int key = 0;
            printf("Enter key: ");
            scanf_s("%d", &key);
            bool isKeyInTree = false;
            depthSearch(tree, &isKeyInTree, key);
            if (isKeyInTree) {
                printf("Key in tree!");
            } else {
                printf("Key not in tree!");
            }
        } else {
            printTree(tree);
        }
        showMenu();
        printf("Enter command: ");
        scanf_s("%d", &choice);
    }
    deleteTree(&tree);
    printf("\n");
}