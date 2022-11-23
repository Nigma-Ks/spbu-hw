#include <stdlib.h>
#include <stdio.h>

#include "listOfDates.h"

typedef struct ListElement {
    int day;
    int month;
    int year;
    struct ListElement *next;
} ListElement;

typedef struct List {
    ListElement *firstElement;
    int lenList;
} List;

int listLen(List *list) {
    if (list == NULL) {
        return -2;
    }
    return list->lenList;
}

List *createList() {
    List *memory = calloc(1, sizeof(List));
    memory->lenList = 0;
    return memory;
}

int insert(List *list, int day, int month, int year) {
    if (list == NULL) {
        return -2;
    }
    if (list->firstElement == NULL) {
        list->firstElement = calloc(1, sizeof(ListElement));
        if (list->firstElement == NULL) {
            return -1;
        }
        list->firstElement->month = month;
        list->firstElement->year = year;
        list->firstElement->day = day;
        list->firstElement->next = NULL;
        list->lenList = 1;
        return 0;
    }
    ListElement *curr = list->firstElement;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    ListElement *insertion = calloc(1, sizeof(ListElement));
    if (insertion == NULL) {
        return -1;
    }
    insertion->month = month;
    insertion->day = day;
    insertion->year = year;
    insertion->next = NULL;
    curr->next = insertion;
    list->lenList++;
    return 0;
}


int getValueByIndex(List *list, int index, int *day, int *month, int *year) {
    if (list == NULL) {
        return -2;
    }
    if (index >= list->lenList) {
        return -3;
    }
    ListElement *curr = list->firstElement;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    *day = curr->day;
    *month = curr->month;
    *year = curr->year;
    return 0;
}


int printList(List *list) {
    if (list == NULL) {
        return -2;
    }
    ListElement *curr = list->firstElement;
    if (curr == NULL) {
        printf("No elements\n");
        return 0;
    }
    int number = 1;
    while (curr != NULL) {
        printf("%d. %d.%d.%d\n", number, curr->day, curr->month, curr->year);
        number++;
        curr = curr->next;
    }
    return 0;
}

int deleteList(List *list) {
    if (list != NULL) {
        ListElement *curr = list->firstElement;
        while (curr != NULL) {
            ListElement *forDel = curr;
            curr = curr->next;
            free(forDel);
        }
        free(list);
        list = NULL;
        return 0;
    }
    return -1;
}