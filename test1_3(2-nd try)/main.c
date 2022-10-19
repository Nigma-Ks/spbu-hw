#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define testFilePath "C:\\Users\\Huawei\\CLionProjects\\test1(snd try)\\Testfile"

int main() {
    FILE *file = fopen(testFilePath, "r");
    printf("This program shows you all symbols in your file and their amounts\n");
    char *symbols = "`1234567890-=~!@#$%^&*()_+qwertyuiop[]QWERTYUIOP{}asdfghjkl;'ASDFGHJKL:zxcvbnm,./ZXCVBNM<>?|";
    int amountOfSymbols = strlen(symbols);
    int *arrayWithSymbolsAmounts = calloc(amountOfSymbols + 3, sizeof(int));
    char specificSymbol1 = '\\';
    char specificSymbol2 = '"';
    char symbolInFile = '1';
    while (fscanf(file, "%c", &symbolInFile) != EOF) {
        char *pSymbolInStrOfSymbols = strchr(symbols, (int) symbolInFile);
        if (pSymbolInStrOfSymbols != NULL) {
            int position = pSymbolInStrOfSymbols - symbols;
            arrayWithSymbolsAmounts[position]++;
        } else if (specificSymbol1 == symbolInFile) {
            arrayWithSymbolsAmounts[amountOfSymbols]++;
        } else if (specificSymbol2 == symbolInFile) {
            arrayWithSymbolsAmounts[amountOfSymbols + 1]++;
        } else {
            arrayWithSymbolsAmounts[amountOfSymbols + 2]++; //this symbol - \n
        }
    }
    printf("Symbols in your file:\n");
    for (int i = 0; i < amountOfSymbols; i++) {
        if (arrayWithSymbolsAmounts[i]) {
            printf("%c: %d\n", symbols[i], arrayWithSymbolsAmounts[i]);
        }
    }
    if (arrayWithSymbolsAmounts[amountOfSymbols]) {
        printf("%c: %d\n", specificSymbol1, arrayWithSymbolsAmounts[amountOfSymbols]);
    }
    if (arrayWithSymbolsAmounts[amountOfSymbols + 1]) {
        printf("%c: %d\n", specificSymbol2, arrayWithSymbolsAmounts[amountOfSymbols + 1]);
    }
    if (arrayWithSymbolsAmounts[amountOfSymbols + 2]) {
        printf("next line symbols: %d\n", arrayWithSymbolsAmounts[amountOfSymbols + 2]);
    }
    fclose(file);
    return 0;
}
