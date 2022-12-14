#include <stdio.h>
#include "list.h"

void showMenu() {
    printf("\nyou can enter this commands to:\n"
           "0 - stop program\n"
           "1 - add new value in the sorted list\n"
           "2 - delete value by index from sorted list\n"
           "3 - change value by index1 and value by index1 on sum of values\n"
           "4 - print sorted list\n");
}

int main() {
    printf("This program creates sorted list, then");
    showMenu();
    struct SortedList *sortedList = create();
    int choice = 0;
    printf("Enter command: ");
    scanf_s("%d", &choice);
    while (choice != 0) {
        while (choice < 0 || choice > 4) {
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
            int index = 0;
            int value = 0;
            printf("Enter index: ");
            scanf_s("%d", &index);
            if (removeValue(sortedList, index, &value)) {
                printf("\nThere is no such index in list\n");
            } else {
                printf("\n%d was removed", value);
            }
        } else if (choice == 3) {
            int index1 = 0;
            int value1 = 0;
            int index2 = 0;
            int value2 = 0;
            printf("Enter index1: ");
            scanf_s("%d", &index1);
            printf("Enter index2: ");
            scanf_s("%d", &index2);
            if (removeValue(sortedList, index1, &value1) || removeValue(sortedList, index2, &value2)) {
                printf("\nThere is no values with those indexes\n");
            } else {
                insert(sortedList, value1 + value2);
                printf("\nElement with value %d was added\n", value1 + value2);
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
