#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "phonelist.h"

#define filePath "..\\phoneList.txt"
#define maxBufferLen 30+17+1
#define maxNameLen 30
#define maxPhoneLen 17

int strCompare(char *fstStr, char *sndStr) {
    int fstLen = strlen(fstStr), sndLen = strlen(sndStr);
    if (fstLen < sndLen) {
        for (int i = 0; i < fstLen; i++) {
            if ((int) fstStr[i] > (int) sndStr[i]) {
                return 1;
            } else if ((int) fstStr[i] < (int) sndStr[i]) {
                return 2;
            }
        }
        return 2;
    }
    for (int i = 0; i < sndLen; i++) {
        if ((int) fstStr[i] > (int) sndStr[i]) {
            return 1;
        } else if ((int) fstStr[i] < (int) sndStr[i]) {
            return 2;
        }
    }
    return 1;
}

void mergeSort(struct PhoneList *phoneList, bool nameOrPhone, int startIndex, int finishIndex) {
    if (finishIndex - startIndex <= 0) {
        return;
    }
    int currIndex = (int) (finishIndex + startIndex) / 2;
    int error = 0;
    struct PhoneList *rightHalf = createSubList(phoneList, 0, currIndex, &error);
    mergeSort(rightHalf, nameOrPhone, 0, currIndex);
    struct PhoneList *leftHalf = createSubList(phoneList, currIndex + 1, finishIndex, &error);
    mergeSort(leftHalf, nameOrPhone, 0, finishIndex - currIndex - 1);
    int n = 0;
    int rightIndex = 0;
    int leftIndex = 0;
    while (n <= finishIndex) {
        if (rightIndex > currIndex) {
            char sndName[maxNameLen] = "";
            char sndPhone[maxPhoneLen] = "";
            getValueByIndex(leftHalf, leftIndex, sndName, sndPhone);
            changeElementValueByIndex(phoneList, n, sndName, sndPhone);
            leftIndex++;
        } else if (leftIndex > finishIndex - currIndex - 1) {
            char fstName[maxNameLen] = "";
            char fstPhone[maxPhoneLen] = "";
            getValueByIndex(rightHalf, rightIndex, fstName, fstPhone);
            changeElementValueByIndex(phoneList, n, fstName, fstPhone);
            rightIndex++;
        } else {
            char fstName[maxNameLen] = "";
            char fstPhone[maxPhoneLen] = "";
            getValueByIndex(rightHalf, rightIndex, fstName, fstPhone);
            char sndName[maxNameLen] = "";
            char sndPhone[maxPhoneLen] = "";
            getValueByIndex(leftHalf, leftIndex, sndName, sndPhone);
            if (nameOrPhone) {//phone
                if (strCompare(fstName, sndName) == 2) {
                    changeElementValueByIndex(phoneList, n, fstName, fstPhone);
                    rightIndex++;
                } else {
                    changeElementValueByIndex(phoneList, n, sndName, sndPhone);
                    leftIndex++;
                }
            } else if (strCompare(fstPhone, sndPhone) == 2) {
                changeElementValueByIndex(phoneList, n, fstName, fstPhone);
                rightIndex++;
            } else {
                changeElementValueByIndex(phoneList, n, sndName, sndPhone);
                leftIndex++;
            }
        }
        n++;
    }
    deleteList(rightHalf);
    deleteList(leftHalf);
}

int phoneListFill(struct PhoneList *phoneList) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return -1;
    }
    char *stringInFile = calloc(maxBufferLen + 1, sizeof(char));
    while (fgets(stringInFile, maxBufferLen, file) != NULL) {
        char *name = calloc(maxNameLen + 1, sizeof(char));
        char *phone = calloc(maxPhoneLen + 1, sizeof(char));
        int strLen = strlen(stringInFile);
        int nameLen = 0;
        for (int i = 0; i < strLen; i++) {
            if (stringInFile[i] != '-') {
                name[i] = stringInFile[i];
            } else {
                nameLen = i;
                break;
            }
        }
        for (int i = nameLen + 1; i < strLen; i++) {
            phone[i - nameLen - 1] = stringInFile[i];
        }
        insert(phoneList, name, phone);
        free(phone);
        free(name);
    }
    free(stringInFile);
    return 0;
}

int main() {
    struct PhoneList *phoneList = createList();
    int resultOfFilling = 0;
    resultOfFilling = phoneListFill(phoneList);
    if (resultOfFilling != 0) {
        printf("Your file wasn't found\n");
        return 0;
    }
    printf("This program sorts your phone list by numbers or by names. \nChoose the way of sorting, enter 1 if by names or 0 if by phones: ");
    int choice = 0;
    scanf_s("%d", &choice);
    while (choice < 0 || choice > 1) {
        printf("Wrong!\nChoose the way of sorting, enter 0 if by names or 1 if by phones: ");
        scanf_s("%d", &choice);
    }
    printf("\nYour list before sorting: \n");
    printList(phoneList);
    mergeSort(phoneList, choice, 0, listLen(phoneList) - 1);
    printf("\nYour list after sorting: \n");
    printList(phoneList);
    deleteList(phoneList);
    return 0;
}
