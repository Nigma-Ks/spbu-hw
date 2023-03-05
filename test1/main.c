#include <stdio.h>
#include <stdbool.h>

#define arraySize 200
#define size 5

void insertionSortOfEven(int arrayForSort[], int startIndex, int finishIndex) {
    if ((finishIndex - startIndex + 1 > 1) && (startIndex >= 0) && (finishIndex >= 0)) {
        int copyOfValue = 0;
        for (int i = startIndex + 1; i <= finishIndex; i++) {
            if (arrayForSort[i] % 2 == 0) {
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

bool testWithZeroEvenNumbers() {
    int arrayForSort[size] = {1, 3, 7, 9, -13};
    int answer[size] = {1, 3, 7, 9, -13};
    insertionSortOfEven(arrayForSort, 0, size - 1);
    for (int i = 0; i < size; i++) {
        if (answer[i] != arrayForSort[i]) {
            return false;
        }
    }
    return true;
}

bool testWithOneEvenNumber() {
    int arrayForSort[size] = {1, 2, 7, 9, -13};
    int answer[size] = {1, 2, 7, 9, -13};
    insertionSortOfEven(arrayForSort, 0, size - 1);
    for (int i = 0; i < size; i++) {
        if (answer[i] != arrayForSort[i]) {
            return false;
        }
    }
    return true;
}

bool testWithTreeEvenNumber() {
    int arrayForSort[size] = {-900, 88, 7, 66, -13};
    int answer[size] = {-900, 66, 7, 88, -13};
    insertionSortOfEven(arrayForSort, 0, size - 1);
    for (int i = 0; i < size; i++) {
        if (answer[i] != arrayForSort[i]) {
            return false;
        }
    }
    return true;
}

bool testWithAllEvenNumber() {
    int arrayForSort[size] = {-900, 88, 0, 66, -80};
    int answer[size] = {-900, -80, 0, 66, 88};
    insertionSortOfEven(arrayForSort, 0, size - 1);
    for (int i = 0; i < size; i++) {
        if (answer[i] != arrayForSort[i]) {
            return false;
        }
    }
    return true;
}

bool testOfTests() {
    if (testWithZeroEvenNumbers() && testWithOneEvenNumber() && testWithTreeEvenNumber() && testWithAllEvenNumber()) {
        return true;
    }
    return false;
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
    if (testOfTests()) {
        printf("\nAll tests are passed");
    } else {
        printf("\nTests are failed");
    }
    printf("\n");
    return 0;
}

