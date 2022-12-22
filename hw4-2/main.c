#include <stdlib.h>
#include <stdbool.h>
#include "sort.h"

#define FILE_PATH "..\\array"
#define TEST1_FILE_PATH "..\\test1_file"
#define TEST2_FILE_PATH "..\\test2_file"

int searchOfMostRepeatedElement(const int arrayWithNumbers[], int amountOfNumbers) {
    int maxAmountOfRepeats = 1, mostRepeatedNumber = arrayWithNumbers[0], repeatsCounter = 1;
    for (int j = 1; j < amountOfNumbers; ++j) {
        if (arrayWithNumbers[j] != arrayWithNumbers[j - 1]) {
            if (maxAmountOfRepeats < repeatsCounter) {
                maxAmountOfRepeats = repeatsCounter;
                mostRepeatedNumber = arrayWithNumbers[j - 1];
            }
            repeatsCounter = 1;
        } else {
            ++repeatsCounter;
        }
    }
    if (maxAmountOfRepeats < repeatsCounter) {
        maxAmountOfRepeats = repeatsCounter; //не используется, но если понадобится количество
        mostRepeatedNumber = arrayWithNumbers[amountOfNumbers - 1]; //повторов, то оно в этой пременной
    }
    return mostRepeatedNumber;
}

void printError(int error) {
    if (error == -1) {
        printf("No file!\n");
        return;
    }
    if (error == -2) {
        printf("Incorrect file!\n");
        return;
    }
    if (error == -4) {
        printf("There are no numbers in file!\n");
        return;
    }
    printf("Memory error!\n");
}

bool testWithWrongFile() {
    int error = 0, amountOfNumbers = 0;
    FILE *testFile1 = fopen(TEST1_FILE_PATH, "a+");
    fprintf(testFile1, "5\nk\n7");
    fclose(testFile1);
    int *testArrayForSort = arrayOfNumbersInFile(TEST1_FILE_PATH, &amountOfNumbers, &error);
    remove(TEST1_FILE_PATH);
    return error == -2;
}

bool testWithRightFile() {
    int error = 0, amountOfNumbers = 0;
    FILE *testFile2 = fopen(TEST2_FILE_PATH, "a+");
    fprintf(testFile2, "5\n5\n7\n5\n7\n8\n90");
    fclose(testFile2);
    int *testArrayForSort = arrayOfNumbersInFile(TEST2_FILE_PATH, &amountOfNumbers, &error);
    quickSort(testArrayForSort, 0, amountOfNumbers - 1);
    int result = searchOfMostRepeatedElement(testArrayForSort, amountOfNumbers);
    free(testArrayForSort);
    remove(TEST2_FILE_PATH);
    return result == 5;
}

int main() {
    if (testWithWrongFile() && testWithRightFile()) {
        printf("Tests were passed!\n");
    } else {
        printf("Tests weren't passed!\n");
    }
    int amountOfNumbers = 0;
    int error = 0;
    int *arrayForSort = arrayOfNumbersInFile(FILE_PATH, &amountOfNumbers, &error);
    if (error) {
        printError(error);
        return 0;
    }
    printf("Your array in file: ");
    for (int i = 0; i < amountOfNumbers; i++) {
        printf("%d ", arrayForSort[i]);
    }
    quickSort(arrayForSort, 0, amountOfNumbers - 1);
    printf("\nYour sorted array: ");
    for (int i = 0; i < amountOfNumbers; i++) {
        printf("%d ", arrayForSort[i]);
    }
    printf("\nThe most repeated number in array is %d\n", searchOfMostRepeatedElement(arrayForSort, amountOfNumbers));
    free(arrayForSort);
    printf("\n");
    return 0;
}


