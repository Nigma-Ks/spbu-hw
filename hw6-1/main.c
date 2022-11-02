#include <stdio.h>
#include "list.h"

void showMenu() {
    printf("\nyou can enter this commands to:\n"
           "0 - stop program\n"
           "1 - add new value in the sorted list\n"
           "2 - delete value from sorted list\n"
           "3 - print sorted list\n");
}

int main() {
    printf("This program creates sorted list, then");
    showMenu();
    struct SortedList *sortedList = create();
    int choice = 0;
    printf("Enter command: ");
    scanf_s("%d", &choice);
    while (choice != 0) {
        while (choice < 0 || choice > 3) {
            printf("\nWrong choice\n");
            showMenu();
            printf("Enter command: ");
            scanf_s("%d", &choice);
        }
        if (choice == 1) {
            int value = 0;
            printf("Enter value: ");
            scanf_s("%d", &value);
            insert(sortedList, value);
        } else if (choice == 2) {
            int value = 0;
            printf("Enter value: ");
            scanf_s("%d", &value);
            if (removeValue(sortedList, value)) {
                printf("\nThere is no such value in list\n");
            }
        } else {
            printList(sortedList);
        }
        showMenu();
        printf("Enter command: ");
        scanf_s("%d", &choice);
    }
    deleteList(sortedList);
    printf("\n");
    return 0;
}
