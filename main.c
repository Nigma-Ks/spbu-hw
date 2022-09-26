#include <stdio.h>
#include <stdlib.h>


float exponentiationLinear(float number, int power) {
    if (power == 0) return 1;
    float result = 1;
    for (int i = 1; i <= abs(power); i++) {
        result *= number;
    }
    if (power < 0) return (1 / result);
    return result;
}

float exponentiationLogN(float number, int power) {
    if (power == 0) return 1;
    int absPower = abs(power);
    float result = 1;
    while (absPower != 0) {
        if (absPower & 1) {
            result *= number;
            absPower--;
        }
        number *= number;
        absPower = (int) absPower / 2;
    }
    if (power < 0) return (1 / result);
    return result;
}


int main() {
    printf("This program calculates entered number to the of entered power(if it is integer)\nEnter number: ");
    int power = 0;
    float number = 0;
    scanf_s("%f", &number);
    printf("Enter power: ");
    scanf_s("%d", &power);
    printf("How you want to calculate it? If by quick algorithm enter '1', if by simple algorithm '2'");
    int choice = 0;
    scanf_s("%d", &choice);
    while (!(choice == 1 || choice == 2)) {
        printf("You can enter only '1' or '2'. Try again\nHow you want to calculate it? If by quick algorithm"
               " enter '1', if by simple algorithm '2'");
        scanf_s("%d", &choice);
    }
    if (choice == 2) {
        printf("The result is %f", exponentiationLinear(number, power));
    } else {
        printf("The result is %f", exponentiationLogN(number, power));
    }
    return 0;
}
