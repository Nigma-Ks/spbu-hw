#include <stdio.h>

#define arraySize 200

void shellSort(int arrayForSort[], int sizeOfArray, int step) {
    int copyOfValue = 0;
    for (int i = 0; i < sizeOfArray; i += step) {
        int indexOfCurrentElement = i;
        for (int j = i - step; j >= 0; j -= step) {
            if (arrayForSort[indexOfCurrentElement] < arrayForSort[j]) {
                copyOfValue = arrayForSort[indexOfCurrentElement];
                arrayForSort[indexOfCurrentElement] = arrayForSort[j];
                arrayForSort[j] = copyOfValue;
                indexOfCurrentElement--;
            } else {
                break;
            }
        }
    }
}

int main() {
    printf("This program sorts numbers in your array from small to big numbers\n"
           "Enter amount of elements in array (only 200 and less): ");
    int amountOfElements = 0;
    scanf_s("%d", &amountOfElements);
    while (amountOfElements <= 0 || amountOfElements > 200) {
        printf("This program can't sort array with %d elements\nEnter amount of elements in array "
               "(only 200 and less) again: ", amountOfElements);
        scanf_s("%d", &amountOfElements);
    }
    int arrayForSort[arraySize] = {0};
    for (int i = 0; i < amountOfElements; i++) {
        printf("Enter element: ");
        scanf_s("%d", &arrayForSort[i]);
    }
    for (int stepOfSort = (int) amountOfElements / 2; stepOfSort >= 1; stepOfSort--) {
        shellSort(arrayForSort, amountOfElements, stepOfSort);
    }
    printf("Now your array look like this: ");
    for (int i = 0; i < amountOfElements; i++) {
        printf("%d ", arrayForSort[i]);
    }
    printf("\n");
    return 0;
}
