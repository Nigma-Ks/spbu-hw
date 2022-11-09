#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void evenOddSort(int arrayForSort[], int arraySize) {
    int firstIndexWithOdd = arraySize - 1;
    int copyOfValue = 0;
    for (int i = 0; i < arraySize; i++) {
        if (i >= firstIndexWithOdd) break;
        if (arrayForSort[i] % 2 != 0) {
            while (arrayForSort[firstIndexWithOdd] % 2 != 0 && firstIndexWithOdd > i) {
                firstIndexWithOdd--;
            }
            if (firstIndexWithOdd == i) {
                break;
            }
            copyOfValue = arrayForSort[i];
            arrayForSort[i] = arrayForSort[firstIndexWithOdd];
            arrayForSort[firstIndexWithOdd] = copyOfValue;
            firstIndexWithOdd--;
        }
    }
}

bool testAlgorithmWorks() {
    int arrayForSort[] = {1, 2, 3, 4, 5};
    evenOddSort(arrayForSort, 5);
    bool metOddNumber = false;
    for (int i = 0; i < 5; i++) {
        if (arrayForSort[i] % 2 == 0 && metOddNumber) {
            return false;
        } else if (arrayForSort[i] % 2 != 0) {
            metOddNumber = true;
        }
    }
    return true;
}

bool testIsNaturalSort() {
    int arrayForSort[] = {4, 2, 3, 5, 1};
    int arrayForCompare[] = {4, 2, 3, 5, 1};
    evenOddSort(arrayForSort, 5);
    for (int i = 0; i < 5; i++) {
        if (arrayForSort[i] != arrayForCompare[i]) {
            return false;
        }
    }
    return true;
}

void printArray(int *array, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }
}

int main() {
    if (testAlgorithmWorks() && testIsNaturalSort()) {
        printf("Tests were passed!\n");
    } else {
        printf("Tests were not passed!\n");
    }
    printf("This program sorts your array: the beginning elements will be even, the ending odd\nEnter the amount of elements in array: ");
    int amountNumbersToSort = 0;
    scanf_s("%d", &amountNumbersToSort);
    while (amountNumbersToSort <= 0) {
        printf("you can not sort this amount of elements, try again\nEnter the amount of elements in array: ");
        scanf_s("%d", &amountNumbersToSort);
    }
    int *arrayForSort = calloc(amountNumbersToSort, sizeof(int));
    printf("Now enter elements. The first element: ");
    scanf_s("%d", &arrayForSort[0]);
    for (int i = 1; i < amountNumbersToSort; i++) {
        printf("The next element: ");
        scanf_s("%d", &arrayForSort[i]);
    }
    printf("\nBefore sorting array looks like this\n");
    printArray(arrayForSort, amountNumbersToSort);
    evenOddSort(arrayForSort, amountNumbersToSort);
    printf("\nAfter sorting array looks like this\n");
    printArray(arrayForSort, amountNumbersToSort);
    printf("\n");
}

