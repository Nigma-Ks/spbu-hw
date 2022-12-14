#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LEN 100
#define FILE_PATH "..\\order.txt"

unsigned long long sum = 0;
unsigned long long cost = 0;
unsigned long long amountOfProducts = 0;

void sumCalculation() {
    sum += cost*amountOfProducts;//if cost or amount == 0, sum += 0
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

void costAmountColumnReset(int * indexOfColumn) {
    cost = 0;
    amountOfProducts = 0;
    *indexOfColumn = 1;
}
int readFile() {
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        return -1;
    }
    bool correctString = false;
    char chInFile = '\0';
    int indexOfColumn = 1;
    char* wrongStringBuff = calloc(MAX_STRING_LEN, sizeof(char));
    while (fscanf(file, "%c", &chInFile) != EOF) {
        if (chInFile == '\t') {
            indexOfColumn += 1;//1, 2, 3
        } else if (chInFile == '\n') {
            sumCalculation();
            indexOfColumn = 1;
            cost = 0;
            amountOfProducts = 0;
        } else {
            switch (indexOfColumn) {
                case 2:
                    correctString = amountOrderBuff(chInFile);
                    if (!correctString) {
                        fgets(wrongStringBuff, MAX_STRING_LEN, file);
                        costAmountColumnReset(&indexOfColumn);
                    }
                    break;
                case 3:
                    correctString = costOrderBuff(chInFile);
                    if (!correctString) {
                        fgets(wrongStringBuff, MAX_STRING_LEN, file);
                        costAmountColumnReset(&indexOfColumn);
                    }
                    break;
                default:
                    continue;
            }
        }
    }
    sumCalculation();
    free(wrongStringBuff);
    fclose(file);
    return 0;
}

int main() {
    printf("This program counts sum of order in file\n");
    bool fileOpened = !readFile();
    if (!fileOpened) {
        printf("File wasn't found\n");
        return 0;
    }
    if (sum == 0) {
        printf("There is no goods in order or file incorrect\n");
        return 0;
    }
    printf("Total sum: %llu\n", sum);
    return 0;
}
