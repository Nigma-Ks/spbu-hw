#include <stdio.h>
#define maxAvailableNumber 100000

int main() {
    int numbers[maxAvailableNumber] = {0};
    int maxNumber = 0;
    printf("This program writes simple numbers(positive integers) which are smaller than maxNumber or equal\nWrite maxNumber(it "
           "should be from 2 to 100000):");
    scanf_s("%d", &maxNumber);
    if (maxNumber <=1){
        printf("There are not simple numbers smaller than %d", maxNumber);
        return 0;
    }
    for (int i = 2; i <= maxNumber; i++){
        numbers[i-2] = i;
    }
    int simple_divider=0;
    for (int j = 0; j <= maxNumber; j++) {
        if (numbers[j] != 0) {
            simple_divider = numbers[j];
            for (int k = j+1; k <= maxNumber; k++) {
                if (numbers[k] % simple_divider == 0) {
                    numbers[k] = 0;
                }
            }
        }
    }
    printf("Simple numbers:\n");
    for (int i = 0; i <=maxNumber; i++){
        if (numbers[i] != 0) printf("%d ", numbers[i]);
    }
    return 0;
}
