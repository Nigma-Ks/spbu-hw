#include <stdio.h>
#define rangeOfSort 10001

int main() {
    int numbersForSort[rangeOfSort] = {0}, element = 0;
    printf("This program sorts (from small to big) numbers (from -5000 to 5000) in entered array. Enter elements\n");
    printf("The first element(when you fill your array, enter 5001): ");
    scanf_s("%d", &element);
    if (element == 5001) {
        printf("Your array is empty");
        return 0;
    }
    while (element != 5001) {
        numbersForSort[element + 5000]++;
        printf("The next element(when you fill your array, enter 5001): ");
        scanf_s("%d", &element);
    }
    printf("Now your array looks like this: ");
    for (int i = 0; i < rangeOfSort; i++) {
        for (int j = 0; j < numbersForSort[i]; j++) {
            printf("%d ", i - 5000);
        }
    }
    return 0;
}
