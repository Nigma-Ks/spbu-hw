#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "phonelist.h"

#define maxNameLen 30
#define maxPhoneLen 17

typedef struct PhoneListElement {
    char *name;
    char *phone;
    struct PhoneListElement *next;
} PhoneListElement;

typedef struct PhoneList {
    PhoneListElement *firstElement;
    int lenList;
} PhoneList;

int listLen(PhoneList *phoneList) {
    if (phoneList == NULL) {
        return -2;
    }
    return phoneList->lenList;
}

PhoneList *createList() {
    PhoneList *memory = calloc(1, sizeof(PhoneList));
    memory->lenList = 0;
    return memory;
}

int insert(PhoneList *phoneList, char *name, char *phone) {
    if (phoneList == NULL) {
        return -2;
    }
    if (phoneList->firstElement == NULL) {
        phoneList->firstElement = calloc(1, sizeof(PhoneListElement));
        if (phoneList->firstElement == NULL) {
            return -1;
        }
        phoneList->firstElement->phone = calloc(maxPhoneLen, sizeof(char));
        phoneList->firstElement->name = calloc(maxNameLen, sizeof(char));
        if (phoneList->firstElement->phone == NULL || phoneList->firstElement->name == NULL) {
            return -1;
        }
        strcpy(phoneList->firstElement->phone, phone);
        strcpy(phoneList->firstElement->name, name);
        phoneList->firstElement->next = NULL;
        phoneList->lenList = 1;
        return 0;
    }
    PhoneListElement *curr = phoneList->firstElement;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    PhoneListElement *insertion = calloc(1, sizeof(PhoneListElement));
    if (insertion == NULL) {
        return -1;
    }
    insertion->phone = calloc(maxPhoneLen, sizeof(char));
    insertion->name = calloc(maxNameLen, sizeof(char));
    if (insertion->phone == NULL || insertion->name == NULL) {
        return -1;
    }
    strcpy(insertion->phone, phone);
    strcpy(insertion->name, name);
    insertion->next = NULL;
    curr->next = insertion;
    phoneList->lenList++;
    return 0;
}

PhoneList *createSubList(PhoneList *phoneList, int startIndex, int finishIndex, int *error) {
    if ((startIndex > finishIndex) || (finishIndex > (phoneList->lenList) - 1)) {
        *error = -3;
        return NULL;
    }
    if (phoneList == NULL) {
        *error = -2;
        return NULL;
    }
    PhoneList *memory = createList();

    if (memory == NULL) {
        *error = -1;
        return NULL;
    }
    PhoneListElement *curr = phoneList->firstElement;
    for (int i = 0; i < startIndex; i++) {
        curr = curr->next;
    }
    for (int i = startIndex; i <= finishIndex; i++) {
        int resultOfInsertion = insert(memory, curr->name, curr->phone);
        if (resultOfInsertion) {
            *error = -4;
            return NULL;
        }
        curr = curr->next;
    }
    return memory;
}

int getValueByIndex(PhoneList *phoneList, int index, char *name, char *phone) {
    if (phoneList == NULL) {
        return -2;
    }
    if (index >= phoneList->lenList) {
        return -3;
    }
    PhoneListElement *curr = phoneList->firstElement;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    strcpy(name, curr->name);
    strcpy(phone, curr->phone);
    return 0;
}

int changeElementValueByIndex(PhoneList *phoneList, int index, char *newName, char *newPhone) {
    if (phoneList == NULL) {
        return -2;
    }
    if (index >= phoneList->lenList) {
        return -3;
    }
    PhoneListElement *curr = phoneList->firstElement;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    strcpy(curr->name, newName);
    strcpy(curr->phone, newPhone);
    return 0;
}


int printList(PhoneList *phoneList) {
    if (phoneList == NULL) {
        return -2;
    }
    PhoneListElement *curr = phoneList->firstElement;
    if (curr == NULL) {
        printf("No elements\n");
        return 0;
    }
    int number = 1;
    while (curr != NULL) {
        printf("%d. %s-%s", number, curr->name, curr->phone);
        number++;
        curr = curr->next;
    }
    return 0;
}

int deleteList(PhoneList *phoneList) {
    if (phoneList != NULL) {
        PhoneListElement *curr = phoneList->firstElement;
        while (curr != NULL) {
            PhoneListElement *forDel = curr;
            curr = curr->next;
            free(forDel);
        }
        free(phoneList);
        phoneList = NULL;
        return 0;
    }
    return -1;
}