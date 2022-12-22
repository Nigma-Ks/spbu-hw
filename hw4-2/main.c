#include "sort.h"
#include <stdlib.h>

#define FILE_PATH "..\\array"

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

void printError(int error) {
    if (error == -1) {
        printf("No file!\n");
        return;
    }
    if (error == -2) {
        printf("Incorrect file!\n");
        return;
    }
    if (error == -4) {
        printf("There are no numbers in file!\n");
        return;
    }
    printf("Memory error!\n");
}

int main() {
    int amountOfNumbers = 0;
    int error = 0;
    int *arrayForSort = arrayOfNumbersInFile(FILE_PATH, &amountOfNumbers, &error);
    if (error) {
        printError(error);
        return 0;
    }
    printf("Your array in file: ");
    for (int i = 0; i < amountOfNumbers; i++) {
        printf("%d ", arrayForSort[i]);
    }
    quickSort(arrayForSort, 0, amountOfNumbers - 1);
    printf("\nYour sorted array: ");
    for (int i = 0; i < amountOfNumbers; i++) {
        printf("%d ", arrayForSort[i]);
    }
    printf("\nThe most repeated number in array is %d\n", searchOfMostRepeatedElement(arrayForSort, amountOfNumbers));
    free(arrayForSort);
    printf("\n");
    return 0;
}


