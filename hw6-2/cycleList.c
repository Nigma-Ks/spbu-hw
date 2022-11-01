#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct CycleListElement {
    int value;
    struct CycleListElement *next;
} CycleListElement;

typedef struct CycleList {
    CycleListElement *firstvalue;
} CycleList;

CycleList *createList() {
    return calloc(1, sizeof(CycleList));
}

int push(CycleList *cycleList, int value) {
    if (cycleList == NULL) {
        return -2;
    }
    if (cycleList->firstvalue == NULL) {
        cycleList->firstvalue = calloc(1, sizeof(CycleListElement));

        if (cycleList->firstvalue == NULL) {
            return -1;
        }

        cycleList->firstvalue->value = value;
        cycleList->firstvalue->next = NULL;
        return 0;
    }
    if (cycleList->firstvalue->next == NULL) {
        cycleList->firstvalue->next = calloc(1, sizeof(CycleListElement));

        if (cycleList->firstvalue->next == NULL) {
            return -1;
        }

        cycleList->firstvalue->next->value = value;
        cycleList->firstvalue->next->next = cycleList->firstvalue;
        return 0;
    }
    CycleListElement *insertion = calloc(1, sizeof(CycleListElement));

    if (insertion == NULL) {
        return -1;
    }

    insertion->next = cycleList->firstvalue;
    insertion->value = value;
    CycleListElement *curr = cycleList->firstvalue;
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

    CycleListElement *curr = cycleList->firstvalue;
    if (curr == NULL) {
        return -3;
    }

    if (curr->next == NULL) {
        if (curr->value == value) {
            cycleList->firstvalue = NULL;
            return 0;
        }
        return -3;
    }

    if (curr->next->next == curr) {
        if (curr->value == value) {
            cycleList->firstvalue = cycleList->firstvalue->next;
            cycleList->firstvalue->next = NULL;
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
    if (curr->next != cycleList->firstvalue) {
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
    cycleList->firstvalue = curr;
    return 0;
}

int oneElementInList(CycleList *cycleList) {
    if (cycleList == NULL) {
        return -2;
    }
    return cycleList->firstvalue != NULL && cycleList->firstvalue->next == NULL;
}

int nextValueWithMStep(CycleList *cycleList, int currValue, int m) {
    if (cycleList == NULL) {
        return -2;
    }
    if (cycleList->firstvalue == NULL || cycleList->firstvalue->next == NULL) {
        return -1;
    }
    CycleListElement *curr = cycleList->firstvalue;
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
    CycleListElement *curr = cycleList->firstvalue;
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
    return (cycleList->firstvalue->value);
}

int printList(CycleList *cycleList) {
    if (cycleList == NULL) {
        return -2;
    }
    CycleListElement *curr = cycleList->firstvalue;
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
