#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool isBracketsConnected(char fstChar, char sndChar){
    return ((fstChar == '(') && (sndChar == ')')) ||
           ((fstChar == '{') && (sndChar == '}')) ||
           ((fstChar == '<') && (sndChar == '>')) ||
           ((fstChar == '[') && (sndChar == ']'));
}

bool isClosedBracket(char stringChar){
    return (stringChar == '}') || (stringChar == ')') || (stringChar == ']') || (stringChar == '>');
}

bool isOpenBracket(char stringChar){
    return (stringChar == '{') || (stringChar == '(') || (stringChar == '[') || (stringChar == '<');
}


int main() {
    printf("Enter string with brackets(you can enter only 100 chars and less) which you want to check: ");
    char stringWithBrackets[100] = "";
    char stackString[100] = "";
    int stackLen = 0;
    scanf_s("%s",  stringWithBrackets);
    for (int i = 0; i < strlen(stringWithBrackets);++i) {
        if (isOpenBracket(stringWithBrackets[i])) {
            stackString[stackLen] = stringWithBrackets[i];
            stackLen++;
        } else if (isClosedBracket(stringWithBrackets[i])) {
            if (stackLen != 0) {
                if (isBracketsConnected(stackString[stackLen - 1], stringWithBrackets[i])) {
                    stackString[stackLen - 1] = '\0';
                    stackLen--;
                }else{
                    stackString[stackLen] = stringWithBrackets[i];
                    stackLen++;
                }
            } else {
                printf("This string with brackets isn't right");
                return 0;
            }
        }
    }
    if (stackLen != 0) {
        printf("This string with brackets isn't right");
    }else{
        printf("This string with brackets is right");
    }
    return 0;
}