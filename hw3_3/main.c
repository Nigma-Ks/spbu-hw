#include <stdio.h>
#include <stdlib.h>

int searchOfMostRepeatedElementInSortedArray(const int arrayWithNumbers[], int amountOfNumbers) {
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

int main() {
    printf("This program finds in entered array element which repeats more often\nEnter the amount of numbers in array: ");
    int amountOfNumbers = 0;
    scanf_s("%d", &amountOfNumbers);
    while (amountOfNumbers <= 0) {
        printf("Incorrect input, try again\nEnter the amount of numbers in array: ");
        scanf_s("%d", &amountOfNumbers);
    }
    int *arrayWithNumbers = (int *) calloc(amountOfNumbers, sizeof(int));
    for (int i = 0; i < amountOfNumbers; i++) {
        printf("Enter element: ");
        scanf_s("%d", &arrayWithNumbers[i]);
    }
    quickSort(arrayWithNumbers, 0, amountOfNumbers - 1);
    printf("The most repeated number in array is %d\n", searchOfMostRepeatedElementInSortedArray(arrayWithNumbers, amountOfNumbers));
    free(arrayWithNumbers);
    return 0;
}
