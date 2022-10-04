#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define range 5000

void quickSort(int arrayForSort[], int startIndex, int finishIndex) {
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

bool binarySearch(const int arrayInWhichFind[], int amountOfElementsInArray, int elementToFind) {
    int startIndex = 0, finishIndex = amountOfElementsInArray, currIndex = 0;
    while (startIndex != finishIndex) {
        currIndex = (int) (finishIndex - startIndex) / 2 + startIndex;
        if (elementToFind > arrayInWhichFind[currIndex]) {
            if (startIndex == currIndex) break; //избегаем ситуации бесконечного цикла
            startIndex = currIndex;
        } else if (elementToFind < arrayInWhichFind[currIndex]) {
            finishIndex = currIndex;
        } else {
            return true;
        }
    }
    if (arrayInWhichFind[finishIndex] == elementToFind) { //finish потому что округление вниз,
        return true;
    }
    return false;
}

int main() {
    srand(time(0));
    printf("This program generates array with n integer elements (from -%d to %d), \nthen generates k integer "
           "numbers (from -%d to %d)\nthen checks if any of k numbers in array\nEnter n: ",
           (int) range / 2, (int) range / 2, (int) range / 2, (int) range / 2);
    int amountOfElements = 0, amountOfElementsToFind = 0;
    scanf_s("%d", &amountOfElements);
    while (amountOfElements <= 0) {
        printf("Incorrect input, try again\nEnter n: ");
        scanf_s("%d", &amountOfElements);
    }
    printf("Enter k: ");
    scanf_s("%d", &amountOfElementsToFind);
    while (amountOfElementsToFind <= 0) {
        printf("Incorrect input, try again\nEnter k: ");
        scanf_s("%d", &amountOfElementsToFind);
    }
    int *arrayInWhichFind = (int *) calloc(amountOfElements, sizeof(int));
    int *arrayWithElementsToFind = (int *) calloc(amountOfElementsToFind, sizeof(int));
    printf("Your array with n elements: ");
    for (int i = 0; i < amountOfElements; i++) {
        arrayInWhichFind[i] = rand() % (range + 1) - (int) range / 2;
        printf("%d ", arrayInWhichFind[i]);
    }
    quickSort(arrayInWhichFind, 0, amountOfElements);
    printf("\nYour k elements: \n");
    for (int j = 0; j < amountOfElementsToFind; j++) {
        arrayWithElementsToFind[j] = rand() % (range + 1) - (int) range / 2;
        printf("%d ", arrayWithElementsToFind[j]);
    }
    printf("\n\n");
    bool isAnyElementInArray = false;
    for (int x = 0; x < amountOfElementsToFind; x++) {
        if (binarySearch(arrayInWhichFind, amountOfElements, arrayWithElementsToFind[x])) {
            printf("%d ", arrayWithElementsToFind[x]);
            isAnyElementInArray = true;
        }
    }
    free(arrayInWhichFind);
    free(arrayWithElementsToFind);
    if (isAnyElementInArray) {
        printf("- numbers in array\n");
        return 0;
    }
    printf("There is no of k numbers in array\n");
    return 0;
}
