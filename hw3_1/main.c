#include <stdio.h>

#define MAX_ARRAY_SIZE 200

void insertionSort(float arrayForSort[], int startIndex, int finishIndex) {
    if (finishIndex > startIndex && startIndex >= 0 && finishIndex >= 0) {
        float copyOfValue = 0;
        for (int i = startIndex + 1; i <= finishIndex; i++) {
            for (int j = i - 1; j >= startIndex && arrayForSort[j + 1] < arrayForSort[j]; j--) {
                copyOfValue = arrayForSort[j + 1];
                arrayForSort[j + 1] = arrayForSort[j];
                arrayForSort[j] = copyOfValue;
            }
        }
    }
}

void choiceOfSort(int startIndex, int finishIndex, float arrayForSort[]);

void quickSort(float arrayForSort[], int startIndex, int finishIndex) {
    if (finishIndex > startIndex && startIndex >= 0 && finishIndex >= 0) {
        int firstIndexWithBigger = finishIndex;
        float elementForComparison = arrayForSort[startIndex], copyOfValue = 0;
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
        choiceOfSort(startIndex, firstIndexWithBigger - 1, arrayForSort);
        choiceOfSort(firstIndexWithBigger + 1, finishIndex, arrayForSort);
    }
}

void choiceOfSort(int startIndex, int finishIndex, float arrayForSort[]) {
    if (finishIndex > startIndex && startIndex >= 0 && finishIndex >= 0) {
        if (finishIndex - startIndex + 1 < 10) { //amount of elements < 10
            insertionSort(arrayForSort, startIndex, finishIndex);
        } else {
            quickSort(arrayForSort, startIndex, finishIndex);
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
    float arrayForSort[MAX_ARRAY_SIZE] = {0};
    for (int i = 0; i < amountOfElements; i++) {
        printf("Enter element: ");
        scanf_s("%f", &arrayForSort[i]);
    }
    choiceOfSort(0, amountOfElements - 1, arrayForSort);
    printf("Now your array look like this: ");
    for (int i = 0; i < amountOfElements; i++) {
        printf("%0.1f ", arrayForSort[i]);
    }
    printf("\n");
    return 0;
}
