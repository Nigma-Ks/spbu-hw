#include "sort.h"

int main() {
    FILE *file = fopen("C:\\Users\\Huawei\\Desktop\\HW\\spbu-hw\\hw4-2\\array", "r");
    if (file == NULL) {
        printf("file not found!");
        return 0;
    }
    //C:\Users\Huawei\Desktop\HW\spbu-hw\hw4-2\array
    int amountOfNumbers = amountOfNumbersInFile(file);
    int *arrayForSort = calloc(amountOfNumbers, sizeof(int));
    fseek(file, 0, SEEK_SET);
    int linesRead = 0;
    while (!feof(file)) {
        if (fscanf(file, "%d", &arrayForSort[linesRead]) != 1) {
            break;
        }
        ++linesRead;
    }
    fclose(file);
    printf("Your array in file: ");
    for (int i = 0; i < linesRead; i++) {
        printf("%d ", arrayForSort[i]);
    }
    quickSort(arrayForSort, 0, amountOfNumbers - 1);
    printf("\nYour sorted array: ");
    for (int i = 0; i < linesRead; i++) {
        printf("%d ", arrayForSort[i]);
    }
    printf("\n");
    return 0;
}
