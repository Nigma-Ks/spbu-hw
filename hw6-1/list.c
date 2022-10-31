#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct SortedListElement {
    int value;
    struct SortedListElement *next;
} SortedListElement;

typedef struct SortedList {
    SortedListElement *next;
} SortedList;

SortedList *create() {
    SortedList *sortedList = calloc(1, sizeof(SortedList));
    return sortedList;
}

int insert(SortedList *sortedList, int value) {
    if (sortedList == NULL) {
        return -2;
    }
    SortedListElement *curr = sortedList->next;
    if (curr == NULL) {
        sortedList->next = calloc(1, sizeof(SortedListElement));

        if (sortedList->next == NULL) {
            return -1;
        }

        sortedList->next->next = NULL;
        sortedList->next->value = value;
        return 0;
    }
    while ((curr->value < value) && (curr->next != NULL)) {
        curr = curr->next;
    }
    if (curr->next == NULL && curr->value < value) {
        curr->next = calloc(1, sizeof(SortedListElement));

        if (curr->next == NULL) {
            return -1;
        }

        curr->next->value = value;
        curr->next->next = NULL;
        return 0;
    }
    SortedListElement *insertion = calloc(1, sizeof(SortedListElement));

    if (insertion == NULL) {
        return -1;
    }

    insertion->value = curr->value;
    insertion->next = curr->next;
    curr->value = value;
    curr->next = insertion;
    return 0;
}

int removeValue(SortedList *sortedList, int value) {
    if (sortedList == NULL) {
        return -2;
    }
    SortedListElement *curr = sortedList->next;
    if (curr == NULL) {
        return -1;
    }
    while (curr->value != value) {
        curr = curr->next;
        if (curr == NULL) {
            return -1;
        }
    }
    if (curr->next == NULL) {
        free(curr);
        return 0;
    }
    curr->value = curr->next->value;
    SortedListElement *forDel = curr->next;
    curr->next = curr->next->next;
    free(forDel);
    return 0;
}

void deleteList(SortedList *sortedList) {
    if (sortedList != NULL) {
        SortedListElement *curr = sortedList->next;
        while (curr != NULL) {
            SortedListElement *forDel = curr;
            curr = curr->next;
            free(forDel);
        }
        free(sortedList);
    }
}

int printList(SortedList *sortedList) {
    if (sortedList == NULL) {
        return -2;
    }
    SortedListElement *curr = sortedList->next;
    printf("\nYour sorted list: ");
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
    return 0;
}