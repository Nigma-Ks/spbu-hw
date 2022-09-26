#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define arraySize 5

int main() {
    srand(time(0));
    int firstIndexWithBigger = arraySize - 1;
    int arrayForSort[arraySize] = {0};
    printf("This program generates array with 10 elements "
           "(random numbers), then sorts it: the beginning elements will be smaller"
           " then first the ending bigger or equal");
    printf("\nBefore sorting array looks like this\n");
    for (int i = 0; i < arraySize; i++) {
        arrayForSort[i] = rand() % 5001 - 2500;
        printf("%d ", arrayForSort[i]);
    }
    int elementForComparison = arrayForSort[0], copyOfValue = 0;
    for (int i = 0; i < arraySize; i++) {
        if (i >= firstIndexWithBigger) break;
        if (arrayForSort[i] >= elementForComparison){
            copyOfValue = arrayForSort[i];
            arrayForSort[i] = arrayForSort[firstIndexWithBigger];
            arrayForSort[firstIndexWithBigger] = copyOfValue;
            firstIndexWithBigger--;
            i--;
        }
    }
    printf("\nAfter sorting array looks like this\n");
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", arrayForSort[i]);
    }
}
