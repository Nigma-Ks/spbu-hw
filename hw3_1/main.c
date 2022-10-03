#include <stdio.h>

#define arraySize 200

void insertionSort(float arrayForSort[], int startIndex, int finishIndex) {
    if ((finishIndex - startIndex + 1 > 1) && (startIndex >= 0) && (finishIndex >= 0)) {
        float copyOfValue = 0;
        for (int i = startIndex + 1; i <= finishIndex; i++) {
            int indexOfCurrentElement = i;
            for (int j = i - 1; j >= startIndex; j--) {
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

void quickSort(float arrayForSort[], int startIndex, int finishIndex) {
    if ((startIndex >= 0) && (finishIndex >= 0)) {
        int firstIndexWithBigger = finishIndex;
        float elementForComparison = arrayForSort[startIndex], copyOfValue = 0;
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
        /*
         Дальше проверка элемента с индексом firstIndexWithBigger, если он больше или равен elementForComparizon ставим
         0-элемент(elementForComparizon) перед ним, меняя местами с элементом с индексом firstIndexWithBigger-1, иначе вместо элемента с
         индексом firstIndexWithBigger, меняя местами с ним же.
         */
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
        if (firstIndexWithBigger - startIndex < 10) {
            insertionSort(arrayForSort, startIndex, firstIndexWithBigger - 1);
        } else {
            quickSort(arrayForSort, startIndex, firstIndexWithBigger - 1);
        }
        if (finishIndex - firstIndexWithBigger < 10) {
            insertionSort(arrayForSort, firstIndexWithBigger + 1, finishIndex);
        } else {
            quickSort(arrayForSort, firstIndexWithBigger + 1, finishIndex);
        }
    }
}

int main() {
    printf("This program sorts your array from small to big numbers\n"
           "Enter amount of elements in array (only 200 and less): ");
    int amountOfElements = 0;
    scanf_s("%d", &amountOfElements);
    while (amountOfElements <= 0 || amountOfElements > 200) {
        printf("This program can't sort array with %d elements\nEnter amount of elements in array "
               "(only 200 and less) again: ", amountOfElements);
        scanf_s("%d", &amountOfElements);
    }
    float arrayForSort[arraySize] = {0};
    for (int i = 0; i < amountOfElements; i++) {
        scanf_s("%f", &arrayForSort[i]);
    }
    if (amountOfElements < 10) {
        insertionSort(arrayForSort, 0, amountOfElements - 1);
    } else {
        quickSort(arrayForSort, 0, amountOfElements - 1);
    }
    printf("Now your array look like this: ");
    for (int i = 0; i < amountOfElements; i++) {
        printf("%0.1f ", arrayForSort[i]);
    }
    printf("\n");
    return 0;
}
