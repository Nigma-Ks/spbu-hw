#include <stdio.h>
#include <stdbool.h>

#define FILE_PATH "..\\order.txt"

unsigned long long sum = 0;
unsigned long long cost = 0;
unsigned long long amountOfProducts = 0;

void sumCalculation() {
    sum += cost * amountOfProducts;//if cost or amount == 0, sum += 0
}

bool costOrderBuff(char chInFile) {
    if (chInFile >= '0' && chInFile <= '9') { //can't be < 0
        cost = cost * 10 + (chInFile - '0');
        return true;
    }
    return false;
}

bool amountOrderBuff(char chInFile) { //can't be < 0
    if (chInFile >= '0' && chInFile <= '9') {
        amountOfProducts = amountOfProducts * 10 + (chInFile - '0');
        return true;
    }
    return false;
}

void costAmountColumnReset(int *indexOfColumn) {
    cost = 0;
    amountOfProducts = 0;
    *indexOfColumn = 1;
}

int readFile(bool *wrongStringsInFile) {
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        return -1;
    }
    bool correctString = false;
    char chInFile = '\0';
    int indexOfColumn = 1;
    while (fscanf(file, "%c", &chInFile) != EOF) {
        if (chInFile == '\t') {
            indexOfColumn += 1;
            if (indexOfColumn > 3) {
                *wrongStringsInFile = true;
                fclose(file);
                return 0;
            }
        } else if (chInFile == '\n') {
            sumCalculation();
            costAmountColumnReset(&indexOfColumn);
        } else {
            switch (indexOfColumn) {
                case 2:
                    correctString = amountOrderBuff(chInFile);
                    if (!correctString) {
                        *wrongStringsInFile = true;
                        fclose(file);
                        return 0;
                    }
                    break;
                case 3:
                    correctString = costOrderBuff(chInFile);
                    if (!correctString) {
                        *wrongStringsInFile = true;
                        fclose(file);
                        return 0;
                    }
                    break;
                default:
                    continue;
            }
        }
    }
    sumCalculation();
    fclose(file);
    return 0;
}

int main() {
    printf("This program counts sum of order in file\n");
    bool wrongStringsInFile = false;
    bool fileOpened = !readFile(&wrongStringsInFile);
    if (!fileOpened) {
        printf("File wasn't found\n");
        return 0;
    }
    if (wrongStringsInFile) {
        printf("File incorrect\n");
        return 0;
    }
    printf("Total sum: %llu\n", sum);
    return 0;
}
