#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STRING_LEN 256
#define MAX_TWO_POWER 4
#define AMOUNT_OF_DIGIT 3

int lenOctNotationCount(int lenOfBinNotation) {
    if (lenOfBinNotation % AMOUNT_OF_DIGIT) {
        return ((int) lenOfBinNotation / AMOUNT_OF_DIGIT) + 1;
    }
    return (int) lenOfBinNotation / AMOUNT_OF_DIGIT;
}

int twoInStartPower(int lenOfBinNotation) {
    int twoInStartPower = 1;
    int amountOfNumbersInLastIncompletedTriple = lenOfBinNotation % AMOUNT_OF_DIGIT;
    if (amountOfNumbersInLastIncompletedTriple) {
        int startPower = amountOfNumbersInLastIncompletedTriple - 1;
        for (int i = 0; i < startPower; i++) {
            twoInStartPower *= 2;
        }
        return twoInStartPower;
    }
    return MAX_TWO_POWER;
}

int binaryNotationToOctalNotation(const char *binNotationOfNumber, char *octNotationOfNumber, int lenOfBinNotation) {
    int twoInCurrPower = twoInStartPower(lenOfBinNotation);
    int currOctNumber = 0;
    int currIndexInOctNumberNotation = 0;
    for (int i = 0; i < lenOfBinNotation; i++) {
        int currNumberInBinNotation = binNotationOfNumber[i] - '0';
        if (currNumberInBinNotation > 1 || currNumberInBinNotation < 0) {
            return false;
        }
        if (!twoInCurrPower) {
            twoInCurrPower = MAX_TWO_POWER;
            octNotationOfNumber[currIndexInOctNumberNotation] = (char) ('0' + currOctNumber);
            currOctNumber = 0;
            currIndexInOctNumberNotation++;
        }
        currOctNumber += currNumberInBinNotation * twoInCurrPower;
        twoInCurrPower = (int) twoInCurrPower / 2;
    }
    octNotationOfNumber[currIndexInOctNumberNotation] = (char) ('0' + currOctNumber);
    return true;
}

void removeInsignificantZeros(char *notationOfNumber, int *lenOfNotation) {
    char *rightNotation = calloc(*lenOfNotation, sizeof(char));
    int rightNotationIndex = 0;
    bool onlyZerosBefore = true;
    for (int i = 0; i < *lenOfNotation - 1; i++) {
        if (notationOfNumber[i] != '0') {
            onlyZerosBefore = false;
        }
        if (!onlyZerosBefore) {
            rightNotation[rightNotationIndex] = notationOfNumber[i];
            rightNotationIndex++;
        }
    }
    rightNotation[rightNotationIndex] = notationOfNumber[*lenOfNotation - 1];
    *lenOfNotation = rightNotationIndex + 1;
    strcpy(notationOfNumber, rightNotation);
    free(rightNotation);
}

int main() {
    printf("This program takes the binary notation of a number and outputs its octal notation\n"
           "Enter string with 256 and less symbols: ");
    char binNotationOfNumber[MAX_STRING_LEN + 1] = {0};
    scanf_s("%256s", binNotationOfNumber);
    int lenOfBinNotation = (int) strlen(binNotationOfNumber);
    if (!lenOfBinNotation) {
        printf("There is no string\n");
        return 0;
    }
    removeInsignificantZeros(binNotationOfNumber, &lenOfBinNotation);
    int lenOfOctNotation = lenOctNotationCount(lenOfBinNotation);
    char *octNotationOfNumber = calloc(lenOfOctNotation + 1, sizeof(char));
    bool result = binaryNotationToOctalNotation(binNotationOfNumber, octNotationOfNumber, lenOfBinNotation);
    if (result) {
        printf("Result: %s\n", octNotationOfNumber);
        free(octNotationOfNumber);
        return 0;
    }
    free(octNotationOfNumber);
    printf("Entered string is incorrect\n");
}
