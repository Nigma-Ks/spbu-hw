#include <stdio.h>
#include <string.h>

int main() {
    printf("This program counts amount of zero-elements(0) in array\nEnter elements(only 100 and less chars in "
           "elements) of the array\nWhen your array will be over, enter 'stop'\nThe first element:");
    char element[100] = "";
    int counterZeros = 0;
    char* stringZero = "0";
    scanf_s("%s", element);
    while (strcmp(element, "stop") != 0) {
        if (strcmp(element, stringZero) == 0){
            counterZeros++;
        }
        printf("The next element:");
        scanf_s("%s", element);
    }
    printf("The amount of zeros: %d", counterZeros);
    return 0;
}
