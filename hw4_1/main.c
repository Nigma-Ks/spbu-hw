#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define intSize 8
#define twoInPower 256

int toDec(char *binNumber) {
    int result = 0, twoInCurrPower = 1;
    for (int i = intSize - 1; i >= 0; i--) {
        if (binNumber[i] == '1') {
            result += twoInCurrPower;
        }
        twoInCurrPower *= 2;
    }
    return result;
}

void binSum(char *binFstNumber, char *binSndNumber) {
    char forNext = '0';
    for (int i = intSize - 1; i >= 0; i--) {
        if (binFstNumber[i] == '1' && binSndNumber[i] == '1') {
            binFstNumber[i] = forNext;
            forNext = '1';
        } else if (binFstNumber[i] == '1' || binSndNumber[i] == '1') {
            if (forNext == '1') {
                binFstNumber[i] = '0';
                forNext = '1';
            } else {
                binFstNumber[i] = '1';
            }
        } else {
            binFstNumber[i] = forNext;
            forNext = '0';
        }
    }
}

void addZeros(char *strForZeros) {
    int amountOfZeros = intSize - strlen(strForZeros);
    for (int i = 0; i < amountOfZeros; i++) {
        strcat(strForZeros, "0");
    }
}

void reverseStr(char *strForReverse) {
    char forChange = ' ';
    for (int i = 0; i < (int) intSize / 2; i++) {
        forChange = strForReverse[i];
        strForReverse[i] = strForReverse[intSize - i - 1];
        strForReverse[intSize - i - 1] = forChange;
    }
}

void convertToBinString(char *strForNumber, int number) {
    while (number != 0) {
        if (number & 1) {
            strcat(strForNumber, "1");
        } else {
            strcat(strForNumber, "0");
        }
        number = number >> 1;
    }
    addZeros(strForNumber);
    reverseStr(strForNumber);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int fstNumber = 0, sndNumber = 0;
    char *binFstNumber = calloc(intSize, sizeof(char));
    char *binSndNumber = calloc(intSize, sizeof(char));
    printf("Введите два числа\nПервое число: ");
    scanf_s("%d", &fstNumber);
    printf("Второе число: ");
    scanf_s("%d", &sndNumber);
    if (fstNumber < 0) {
        fstNumber = twoInPower + fstNumber;
    }
    if (sndNumber < 0) {
        sndNumber = twoInPower + sndNumber;
    }
    convertToBinString(binFstNumber, fstNumber);
    convertToBinString(binSndNumber, sndNumber);
    printf("\nПервое число в двоичной системем счисления: %s\n", binFstNumber);
    printf("Второе число в двоичной системем счисления: %s", binSndNumber);
    printf("\n%s\n", binFstNumber);
    printf("+");
    printf("\n%s\n", binSndNumber);
    printf("=");
    binSum(binFstNumber, binSndNumber);
    printf("%s", binFstNumber);
    int result = toDec(binFstNumber);
    printf("\nВ 10 системе счисления = %d\n", result);
    free(binFstNumber);
    free(binSndNumber);
    return 0;
}
