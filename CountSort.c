#include <stdio.h>

#define rangeOfSort 10001

int main() {
    int numbersForSort[rangeOfSort] = {0}, element = 0, amountOfElementsToSort = 0, amountOfEnteredElements = 0;
    printf("This program sorts (from small to big) numbers (from -5000 to 5000) in entered array."
           "\nEnter the amount of elements in array: ");
    scanf_s("%d", &amountOfElementsToSort);
    while (amountOfElementsToSort <= 0) {
        printf("This program can't sort %d elements, try again.\nEnter the amount of elements in array: ",
               amountOfElementsToSort);
        scanf_s("%d", &element);
    }
    while (amountOfEnteredElements != amountOfElementsToSort) {
        printf("Enter element: ");
        scanf_s("%d", &element);
        if (element < -5000 || element > 5000) {
            printf("Numbers have to be from -5000 to 5000, this number will be ignored, enter %d more elements\n",
                   amountOfElementsToSort - amountOfEnteredElements);
        } else {
            numbersForSort[element + 5000]++;
            amountOfEnteredElements++;
        }
    }
    printf("Now your array looks like this: ");
    for (int i = 0; i < rangeOfSort; i++) {
        for (int j = 0; j < numbersForSort[i]; j++) {
            printf("%d ", i - 5000);
        }
    }
    printf("\n");
    return 0;
}
