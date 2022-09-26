#include <stdio.h>
#include <string.h>

int * reverserOfArrays(int array[], int startIndex, int finishIndex) {
    int copyOfValue = 0;
    for (int i = startIndex; i < (int)((finishIndex - startIndex + 1) / 2) + startIndex; i++) {
        copyOfValue = array[i];
        array[i] = array[finishIndex - i + startIndex];
        array[finishIndex - i + startIndex] = copyOfValue;
    }
    return 0;
}

int main() {
    int arrayForSwitch[200] = {0};
    int element = 0, n = 0, m = 0;
    printf(("This program gets array and switches first m elements with last n elements\n"));
    printf("Enter m (length of first subarray in your array, m <= 100): ");
    scanf_s("%d", &m);
    printf("Enter n (length of second subarray in your array, n <= 100): ");
    scanf_s("%d", &n);
    printf("Enter first element of array: ");
    scanf_s("%d", &element);
    arrayForSwitch[0] = element;
    for (int elementInArray = 1; elementInArray < n+m; elementInArray++){
        printf("Enter next element of array: ");
        scanf_s("%d", &arrayForSwitch[elementInArray]);
    }
    int resultArray[200] = {0};
    memcpy(resultArray,
           reverserOfArrays(
                   reverserOfArrays(
                           reverserOfArrays(arrayForSwitch, 0, m + n - 1),
                           0, n - 1),
                   n, m + n - 1),
           (n + m) * 4);
    printf("Success! Now your array look like this: \n");
    for (int elementInArray = 0; elementInArray < n + m; elementInArray++) {
        printf("%d ", resultArray[elementInArray]);
    }
    return 0;
}
