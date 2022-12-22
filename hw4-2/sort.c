#include <stdlib.h>
#include <stdbool.h>
#include "sort.h"


void quickSort(int arrayForSort[], int startIndex, int finishIndex) {
    if (finishIndex > startIndex && startIndex >= 0 && finishIndex >= 0) {
        int firstIndexWithBigger = finishIndex;
        int elementForComparison = arrayForSort[startIndex], copyOfValue = 0;
        int i = startIndex + 1;
        while (i <= finishIndex && i < firstIndexWithBigger) {
            if (arrayForSort[i] >= elementForComparison) {
                copyOfValue = arrayForSort[i];
                arrayForSort[i] = arrayForSort[firstIndexWithBigger];
                arrayForSort[firstIndexWithBigger] = copyOfValue;
                firstIndexWithBigger--;
            } else {
                i++;
            }
        }
        if (arrayForSort[firstIndexWithBigger] >= arrayForSort[startIndex]) {
            copyOfValue = arrayForSort[startIndex];
            arrayForSort[startIndex] = arrayForSort[firstIndexWithBigger - 1];
            arrayForSort[firstIndexWithBigger - 1] = copyOfValue;
            firstIndexWithBigger--;
        } else {
            copyOfValue = arrayForSort[startIndex];
            arrayForSort[startIndex] = arrayForSort[firstIndexWithBigger];
            arrayForSort[firstIndexWithBigger] = copyOfValue;
        }
        quickSort(arrayForSort, startIndex, firstIndexWithBigger - 1);
        quickSort(arrayForSort, firstIndexWithBigger + 1, finishIndex);
    }
}

int *arrayOfNumbersInFile(char *filePath, int *linesRead, int *error) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *error = -1;
        return NULL;
    }
    int amount = 0, value = 0;
    int readResult = 0;
    while (readResult != EOF) {
        readResult = fscanf(file, "%d", &value);
        if (readResult == 0) {
            *error = -2;
            fclose(file);
            return NULL;
        } else if (readResult == 1) {
            amount++;
        }
    }
    fclose(file);
    if (amount == 0) {
        *error = -4;
        return NULL;
    }
    fopen(filePath, "r");
    int *arrayForSort = calloc(amount, sizeof(int));
    if (arrayForSort == NULL) {
        *error = -3;
        fclose(file);
        return NULL;
    }
    *linesRead = 0;
    while (!feof(file)) {
        fscanf(file, "%d", &arrayForSort[*linesRead]);
        ++(*linesRead);
    }
    fclose(file);
    return arrayForSort;
}

