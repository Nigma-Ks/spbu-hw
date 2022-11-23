#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listOfDates.h"

#define filePath "..\\list.txt"
#define maxDayLen 2
#define maxMonthLen 2
#define maxYearLen 4
#define maxBufferLen maxDayLen + maxMonthLen + maxYearLen + 2


int listFill(struct List *list) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return -1;
    }
    char *stringInFile = calloc(maxBufferLen, sizeof(char));
    while (fscanf(file, "%s", stringInFile) != EOF) {
        char *day = calloc(maxDayLen, sizeof(char));
        char *month = calloc(maxMonthLen, sizeof(char));
        char *year = calloc(maxYearLen, sizeof(char));
        int strLen = strlen(stringInFile);
        int dayLen = 0;
        int dayPlusMonthLen = 0;
        for (int i = 0; i < strLen; i++) {
            if (stringInFile[i] != '.') {
                day[i] = stringInFile[i];
            } else {
                dayLen = i;
                break;
            }
        }
        for (int i = dayLen + 1; i < strLen; i++) {
            if (stringInFile[i] != '.') {
                month[i - dayLen - 1] = stringInFile[i];
            } else {
                dayPlusMonthLen = i;
                break;
            }
        }
        for (int i = dayPlusMonthLen + 1; i < strLen; i++) {
            year[i - dayPlusMonthLen - 1] = stringInFile[i];
        }
        insert(list, atoi(day), atoi(month), atoi(year));
        free(month);
        free(day);
        free(year);
    }
    fclose(file);
    free(stringInFile);
    return 0;
}

char *findMaxDate(struct List *list) {
    if (listLen(list) == 0) {
        return "no dates in file";
    }
    int resultDay = 0;
    int resultMonth = 0;
    int resultYear = 0;
    char *result = calloc(maxBufferLen, sizeof(char));
    char *dot = ".";
    for (int i = 0; i < listLen(list); i++) {
        int day = 0;
        int month = 0;
        int year = 0;
        getValueByIndex(list, i, &day, &month, &year);
        if (i == 0) {
            resultDay = day;
            resultMonth = month;
            resultYear = year;
        } else {
            if (year > resultYear) {
                resultYear = year;
                resultMonth = month;
                resultDay = day;
            } else if (year == resultYear) {
                if (month > resultMonth) {
                    resultYear = year;
                    resultMonth = month;
                    resultDay = day;
                } else if (month == resultMonth) {
                    if (day > resultDay) {
                        resultYear = year;
                        resultMonth = month;
                        resultDay = day;
                    }
                }
            }
        }
    }
    char *maxDay = calloc(maxDayLen, sizeof(char));
    itoa(resultDay, maxDay, 10);
    char *maxMonth = calloc(maxMonthLen, sizeof(char));
    itoa(resultMonth, maxMonth, 10);
    char *maxYear = calloc(maxYearLen, sizeof(char));
    itoa(resultYear, maxYear, 10);
    strcat(result, maxDay);
    strcat(result, dot);
    strcat(result, maxMonth);
    strcat(result, dot);
    strcat(result, maxYear);
    free(maxMonth);
    free(maxYear);
    free(maxDay);
    return result;
}

int main() {
    struct List *list = createList();
    int resultOfFilling = 0;
    resultOfFilling = listFill(list);
    if (resultOfFilling != 0) {
        printf("Your file wasn't found\n");
        return 0;
    }
    printf("This program finds max date in file");
    printf("\nYour dates: \n");
    printList(list);
    printf("Max date: %s", findMaxDate(list));
    deleteList(list);
    return 0;
}
