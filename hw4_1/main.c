#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INT_SIZE 32
#define TWO_IN_POWER 4294967296 //2^32

long long toDec(const char *binNumber) {
    long long result = 0, twoInCurrPower = 1;
    for (int i = INT_SIZE - 1; i >= 0; i--) {
        if (binNumber[i] == '1') {
            result += twoInCurrPower;
        }
        twoInCurrPower *= 2;
    }
    if (binNumber[0] == '1') {
        return result - TWO_IN_POWER;
    }
    return result;
}

void binSum(char *binFstNumber, const char *binSndNumber) {
    char forNext = '0';
    for (int i = INT_SIZE - 1; i >= 0; i--) {
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

void reverseStr(char *strForReverse) {
    char forChange = ' ';
    for (int i = 0; i < INT_SIZE / 2; i++) {
        forChange = strForReverse[i];
        strForReverse[i] = strForReverse[INT_SIZE - i - 1];
        strForReverse[INT_SIZE - i - 1] = forChange;
    }
}

void convertToBinString(char *strForNumber, long long number) {
    long long int mask = 1;
    int amountOfShifts = 0;
    while (amountOfShifts != 32) {
        if (number & mask) {
            strcat(strForNumber, "1");
        } else {
            strcat(strForNumber, "0");
        }
        mask <<= 1;
        amountOfShifts++;
    }
    reverseStr(strForNumber);
}

bool testOfTwoOppositeNumbers(bool *callocError) {
    long long fstNumber = 123, sndNumber = -123;
    char *binFstNumber = calloc(INT_SIZE, sizeof(char));
    char *binSndNumber = calloc(INT_SIZE, sizeof(char));
    if (binFstNumber == NULL || binSndNumber == NULL) {
        free(binFstNumber);
        free(binSndNumber);
        *callocError = true;
        return false;
    }
    convertToBinString(binFstNumber, fstNumber);
    convertToBinString(binSndNumber, sndNumber);
    if (strcmp(binFstNumber, "00000000000000000000000001111011") ||
        strcmp(binSndNumber, "11111111111111111111111110000101")) {
        free(binFstNumber);
        free(binSndNumber);
        return false;
    }
    binSum(binFstNumber, binSndNumber);
    if (strcmp(binFstNumber, "00000000000000000000000000000000")) {
        free(binFstNumber);
        free(binSndNumber);
        return false;
    }
    if (toDec(binFstNumber) != 0) {
        free(binFstNumber);
        free(binSndNumber);
        return false;
    }
    free(binFstNumber);
    free(binSndNumber);
    return true;
}

bool testOfTwoNegativeNumbers(bool *callocError) {
    long long fstNumber = -10, sndNumber = -20;
    char *binFstNumber = calloc(INT_SIZE, sizeof(char));
    char *binSndNumber = calloc(INT_SIZE, sizeof(char));
    if (binFstNumber == NULL || binSndNumber == NULL) {
        free(binFstNumber);
        free(binSndNumber);
        *callocError = true;
        return false;
    }
    convertToBinString(binFstNumber, fstNumber);
    convertToBinString(binSndNumber, sndNumber);
    if (strcmp(binFstNumber, "11111111111111111111111111110110") ||
        strcmp(binSndNumber, "11111111111111111111111111101100")) {
        free(binFstNumber);
        free(binSndNumber);
        return false;
    }
    binSum(binFstNumber, binSndNumber);
    if (strcmp(binFstNumber, "11111111111111111111111111100010")) {
        free(binFstNumber);
        free(binSndNumber);
        return false;
    }
    if (toDec(binFstNumber) != -30) {
        free(binFstNumber);
        free(binSndNumber);
        return false;
    }
    free(binFstNumber);
    free(binSndNumber);
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    bool callocError = false;
    if (!testOfTwoOppositeNumbers(&callocError) || !testOfTwoNegativeNumbers(&callocError)) {
        if (callocError) {
            printf("Тесты провалились, ошибка выделения памяти!\n");
            return 0;
        }
        printf("Тесты провалились!\n");
        return 0;
    }
    printf("Тесты пройдены успешно!\n");
    long long fstNumber = 0, sndNumber = 0;
    char *binFstNumber = calloc(INT_SIZE + 1, sizeof(char));
    char *binSndNumber = calloc(INT_SIZE + 1, sizeof(char));
    if (binFstNumber == NULL || binSndNumber == NULL) {
        free(binFstNumber);
        free(binSndNumber);
        printf("\nОшибка выделения памяти\n");
        return 0;
    }
    printf("Введите два числа\nПервое число: ");
    scanf_s("%lld", &fstNumber);
    printf("Второе число: ");
    scanf_s("%lld", &sndNumber);
    if (fstNumber < 0) {
        fstNumber = TWO_IN_POWER + fstNumber;
    }
    if (sndNumber < 0) {
        sndNumber = TWO_IN_POWER + sndNumber;
    }
    convertToBinString(binFstNumber, fstNumber);
    convertToBinString(binSndNumber, sndNumber);
    printf("\nПервое число в двоичной системе счисления: %s\n", binFstNumber);
    printf("Второе число в двоичной системе счисления: %s", binSndNumber);
    printf("\n%s\n", binFstNumber);
    printf("+");
    printf("\n%s\n", binSndNumber);
    printf("=");
    binSum(binFstNumber, binSndNumber);
    printf("%s", binFstNumber);
    long long result = toDec(binFstNumber);
    printf("\nВ 10 системе счисления = %lld\n", result);
    free(binFstNumber);
    free(binSndNumber);
    return 0;
}
