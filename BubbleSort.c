#include <stdio.h>

#define maxAmountOfElements 100


void bubbleSort(float numbersForSort[], int amountNumbersToSort) {
    float copyOfValue = 0;
    for (int i = 0; i < amountNumbersToSort - 1; i++) {
        for (int j = i; j < amountNumbersToSort; j++) {
            if (numbersForSort[i] > numbersForSort[j]) {
                copyOfValue = numbersForSort[i];
                numbersForSort[i] = numbersForSort[j];
                numbersForSort[j] = copyOfValue;
            }
        }
    }
}


int main() {
    printf("This program sorts your array of numbers from small to big numbers\nEnter the amount of elements in "
           "array (only 100 and less): ");
    int amountNumbersToSort = 0;
    float numbersForSort[maxAmountOfElements] = {0};
    scanf_s("%d", &amountNumbersToSort);
    while (amountNumbersToSort <= 0 || amountNumbersToSort > 100) {
        printf("you can not sort this amount of elements, try again\nEnter the amount of elements in array "
               "(only 100 and less): ");
        scanf_s("%d", &amountNumbersToSort);
    }
    printf("Now enter elements. The first element: ");
    scanf_s("%f", &numbersForSort[0]);
    for (int i = 1; i < amountNumbersToSort; i++) {
        printf("The next element: ");
        scanf_s("%f", &numbersForSort[i]);
    }
    bubbleSort(numbersForSort, amountNumbersToSort);
    printf("Now your array looks like this: ");
    for (int i = 0; i < amountNumbersToSort; i++) {
        printf("%0.2f ", numbersForSort[i]);
    }
    printf("\n");
    return 0;
}
