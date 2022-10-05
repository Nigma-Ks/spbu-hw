#include <stdio.h>

#define arraySize 200

void insertionSortOfEven(int arrayForSort[], int startIndex, int finishIndex) {
    if (finishIndex - startIndex + 1 > 1) {
        int copyOfValue = 0;
        for (int i = startIndex + 1; i <= finishIndex; i++) {
            if (arrayForSort[i]%2 == 0) {
                int indexOfCurrentElement = i;
                for (int j = i - 1; j >= startIndex; j--) {
                    if (arrayForSort[j] % 2 == 0) {
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
    }
}

int main() {
    printf("This program sorts even numbers in your array from small to big numbers\n"
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
    insertionSortOfEven(arrayForSort, 0, amountOfElements - 1);
    printf("Now your array look like this: ");
    for (int i = 0; i < amountOfElements; i++) {
        printf("%d ", arrayForSort[i]);
    }
    printf("\n");
    return 0;
}
