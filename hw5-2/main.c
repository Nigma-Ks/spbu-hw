#include <stdio.h>
#include "stack.h"

int isBracketsConnected(char fstChar, char sndChar) {
    return ((fstChar == '(') && (sndChar == ')')) ||
           ((fstChar == '{') && (sndChar == '}')) ||
           ((fstChar == '<') && (sndChar == '>')) ||
           ((fstChar == '[') && (sndChar == ']'));
}

int isClosedBracket(char stringChar) {
    return (stringChar == '}') || (stringChar == ')') || (stringChar == ']') || (stringChar == '>');
}

int isOpenBracket(char stringChar) {
    return (stringChar == '{') || (stringChar == '(') || (stringChar == '[') || (stringChar == '<');
}

int isRightStringOfBrackets(char *stringWithBrackets, int stringLen) {
    int result = 0;
    StackTail *stack = create(&result);
    for (int i = 0; i < stringLen; i++) {
        if (isOpenBracket(stringWithBrackets[i])) {
            push(stack, stringWithBrackets[i]);
        } else if (isClosedBracket(stringWithBrackets[i]) && isEmpty(stack)) {
            return 0;
        } else if (isClosedBracket(stringWithBrackets[i])){
            char currStackValue = '\0';
            tailValue(stack, &currStackValue);
            if (isBracketsConnected(currStackValue, stringWithBrackets[i])) {
                pop(stack, &currStackValue);
            } else {
                push(stack, stringWithBrackets[i]);
            }
        }
    }
    return isEmpty(stack);
}

int main() {
    printf("Enter the amount of chars in string with brackets which you want to check: ");
    int amountOfChars = 0;
    scanf_s("%d", &amountOfChars);
    while (amountOfChars <= 0) {
        printf("Wrong amount of chars, try again\nEnter the amount of chars: ");
        scanf_s("%d", &amountOfChars);
    }
    char *stringWithBrackets = calloc(amountOfChars, sizeof(char));
    printf("Enter string with brackets which you want to check: ");
    scanf_s("%s", stringWithBrackets);
    if (isRightStringOfBrackets(stringWithBrackets, amountOfChars)){
        printf("It's right!\n");
        return 0;
    }
    free(stringWithBrackets);
    printf("It's wrong!\n");
}
