#pragma once

#include <stdio.h>

void quickSort(int *arrayForSort, int startIndex, int finishIndex);

int* arrayOfNumbersInFile(char * filePath, int * linesRead, int* error);
