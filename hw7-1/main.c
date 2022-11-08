#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

typedef enum Error {
    noDict,
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
           "5 - print dictionary\n");
}

int main() {
    struct Dictionary *dictionary = create();
    printf("This program creates dictionary, then");
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
            add(dictionary, key, value);
        } else if (choice == 2) {
            int key = 0;
            printf("Enter key: ");
            scanf_s("%d", &key);
            delete(dictionary, key);
        } else if (choice == 3) {
            int key = 0;
            printf("Enter key: ");
            scanf_s("%d", &key);
            char *value = "\0";
            getValueByKey(dictionary, key, &value);
            printf("Value by entered key: %s", value);
        } else if (choice == 4) {
            int key = 0;
            printf("Enter key: ");
            scanf_s("%d", &key);
            if (isKeyInDict(dictionary, key)) {
                printf("Key in dictionary!");
            } else {
                printf("Key not in dictionary!");
            }
        } else {
            printDict(dictionary);
        }
        showMenu();
        printf("Enter command: ");
        scanf_s("%d", &choice);
    }
    deleteDict(dictionary);
    printf("\n");
}