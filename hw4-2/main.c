#include "sort.h"


void quickSort(int *arrayForSort, int startIndex, int finishIndex) {
    if ((startIndex >= 0) && (finishIndex >= 0) && (finishIndex - startIndex + 1 > 1)) {
        int firstIndexWithBigger = finishIndex;
        int elementForComparison = arrayForSort[startIndex], copyOfValue = 0;
        for (int i = startIndex + 1; i <= finishIndex; i++) {
            if (i >= firstIndexWithBigger) break;
            if (arrayForSort[i] >= elementForComparison) {
                copyOfValue = arrayForSort[i];
                arrayForSort[i] = arrayForSort[firstIndexWithBigger];
                arrayForSort[firstIndexWithBigger] = copyOfValue;
                firstIndexWithBigger--;
                i--;
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

int amountOfNumbersInFile(FILE *file) {
    int amount = 0, value = 0;
    fseek(file, 0, SEEK_SET);
    while (!feof(file)) {
        if (fscanf(file, "%d", &value) != 1) {
            break;
        }
        amount++;
    }
    return amount;
}

int searchOfMostRepeatedElement(const int arrayWithNumbers[], int amountOfNumbers) {
    int maxAmountOfRepeats = 1, mostRepeatedNumber = arrayWithNumbers[0], repeatsCounter = 1;
    for (int j = 1; j < amountOfNumbers; ++j) {
        if (arrayWithNumbers[j] != arrayWithNumbers[j - 1]) {
            if (maxAmountOfRepeats < repeatsCounter) {
                maxAmountOfRepeats = repeatsCounter;
                mostRepeatedNumber = arrayWithNumbers[j - 1];
            }
            repeatsCounter = 1;
        } else {
            ++repeatsCounter;
        }
    }
    if (maxAmountOfRepeats < repeatsCounter) {
        maxAmountOfRepeats = repeatsCounter; //не используется, но если понадобится количество
        mostRepeatedNumber = arrayWithNumbers[amountOfNumbers - 1]; //повторов, то оно в этой пременной
    }
    return mostRepeatedNumber;
}
