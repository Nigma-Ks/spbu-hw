#include <stdio.h>

#define arraySize 200

void shellSort(int arrayForSort[], int amountOfElements) {
    for (int stepOfSort = (int) amountOfElements / 2; stepOfSort >= 1; stepOfSort--) {
        int copyOfValue = 0;
        for (int i = 0; i < amountOfElements; i += stepOfSort) {
            int indexOfCurrentElement = i;
            for (int j = i - stepOfSort; j >= 0; j -= stepOfSort) {
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
    shellSort(arrayForSort, amountOfElements);
    printf("Now your array look like this: ");
    for (int i = 0; i < amountOfElements; i++) {
        printf("%d ", arrayForSort[i]);
    }
    printf("\n");
    return 0;
}
