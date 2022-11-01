#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct CycleListElement {
    int value;
    struct CycleListElement *next;
} CycleListElement;

typedef struct CycleList {
    CycleListElement *next;
} CycleList;

CycleList *createList() {
    return calloc(1, sizeof(CycleList));
}

int push(CycleList *cycleList, int value) {
    if (cycleList == NULL) {
        return -2;
    }
    if (cycleList->next == NULL) {
        cycleList->next = calloc(1, sizeof(CycleListElement));

        if (cycleList->next == NULL) {
            return -1;
        }

        cycleList->next->value = value;
        cycleList->next->next = NULL;
        return 0;
    }
    if (cycleList->next->next == NULL) {
        cycleList->next->next = calloc(1, sizeof(CycleListElement));

        if (cycleList->next->next == NULL) {
            return -1;
        }

        cycleList->next->next->value = value;
        cycleList->next->next->next = cycleList->next;
        return 0;
    }
    CycleListElement *insertion = calloc(1, sizeof(CycleListElement));

    if (insertion == NULL) {
        return -1;
    }

    insertion->next = cycleList->next;
    insertion->value = value;
    CycleListElement *curr = cycleList->next;
    int startValue = curr->value;
    while (curr->next->value != startValue) {
        curr = curr->next;
    }
    curr->next = insertion;
    return 0;
}

int removeByValue(CycleList *cycleList, int value) {
    if (cycleList == NULL) {
        return -2;
    }

    CycleListElement *curr = cycleList->next;
    if (curr == NULL) {
        return -3;
    }

    if (curr->next == NULL) {
        if (curr->value == value) {
            cycleList->next = NULL;
            return 0;
        }
        return -3;
    }

    if (curr->next->next == curr) {
        if (curr->value == value) {
            cycleList->next = cycleList->next->next;
            cycleList->next->next = NULL;
            free(curr);
            return 0;
        }
        free(curr->next);
        curr->next = NULL;
        return 0;
    }

    int startValue = curr->value;
    bool startValueAgain = false;
    while (curr->value != value) {
        curr = curr->next;
        if (curr->value == startValue) {
            startValueAgain = true;
            break;
        }
    }
    if (startValueAgain) {
        return -3;
    }
    if (curr->next != cycleList->next) {
        curr->value = curr->next->value;
        CycleListElement *forDel = curr->next;
        curr->next = curr->next->next;
        free(forDel);
        return 0;
    }
    curr->value = curr->next->value;
    CycleListElement *forDel = curr->next;
    curr->next = curr->next->next;
    free(forDel);
    cycleList->next = curr;
    return 0;
}

int oneElementInList(CycleList *cycleList) {
    if (cycleList == NULL) {
        return -2;
    }
    return cycleList->next != NULL && cycleList->next->next == NULL;
}

int nextValueWithMStep(CycleList *cycleList, int currValue, int m) {
    if (cycleList == NULL) {
        return -2;
    }
    if (cycleList->next == NULL || cycleList->next->next == NULL) {
        return -1;
    }
    CycleListElement *curr = cycleList->next;
    int startValue = curr->value;
    bool startValueAgain = false;
    while (curr->value != currValue && !startValueAgain) {
        curr = curr->next;
        if (curr->value == startValue) {
            startValueAgain = true;
        }
    }
    if (startValueAgain) {
        return -3;
    }
    for (int i = 0; i < m - 1; i++) {
        curr = curr->next;
    }
    return curr->value;
}

int deleteCycleList(CycleList *cycleList) {
    if (cycleList == NULL) {
        return -2;
    }
    CycleListElement *curr = cycleList->next;
    while (curr != NULL) {
        CycleListElement *forDel = curr;
        curr = curr->next;
        free(forDel);
    }
    free(cycleList);
    return 0;
}

int getValueOfFirst(CycleList *cycleList) {
    if (cycleList == NULL) {

        return -2;
    }
    return (cycleList->next->value);
}

int printList(CycleList *cycleList) {
    if (cycleList == NULL) {
        return -2;
    }
    CycleListElement *curr = cycleList->next;
    printf("\nYour list: ");

    if (curr == NULL) {
        printf("\nNo elements\n");
        return 0;
    }

    int startValue = curr->value;
    printf("%d ", startValue);
    curr = curr->next;

    if (curr == NULL) return 0;

    while (curr->value != startValue) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
    return 0;
}