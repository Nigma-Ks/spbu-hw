#include <stdio.h>
#include "stack.h"

int stackExpressionCount(const char *expression, int amountOfChars) {
    int result = 0;
    StackTail *stack = create(&result);
    for (int i = 0; i < amountOfChars; i++) {
        if (expression[i] != '*' && expression[i] != '+' && expression[i] != '-' && expression[i] != '/') {
            int number = (int) expression[i] - 48;
            push(stack, number);
        } else if (expression[i] == '*') {
            int fstNumber = 0;
            pop(stack, &fstNumber);
            int sndNumber = 0;
            pop(stack, &sndNumber);
            push(stack, fstNumber * sndNumber);
        } else if (expression[i] == '/') {
            int fstNumber = 0;
            pop(stack, &fstNumber);
            int sndNumber = 0;
            pop(stack, &sndNumber);
            push(stack, (int) sndNumber / fstNumber);
        } else if (expression[i] == '-') {
            int fstNumber = 0;
            pop(stack, &fstNumber);
            int sndNumber = 0;
            pop(stack, &sndNumber);
            push(stack, sndNumber - fstNumber);
        } else {
            int fstNumber = 0;
            pop(stack, &fstNumber);
            int sndNumber = 0;
            pop(stack, &sndNumber);
            push(stack, sndNumber + fstNumber);
        }
    }
    int answer;
    pop(stack, &answer);
    free(stack);
    return answer;
}

int main() {
    printf("Enter arithmetic reverse polish expression and how many chars are there.\nAmount of chars in expression: ");
    int amountOfChars = 0;
    scanf_s("%d", &amountOfChars);
    char *expression = calloc(amountOfChars, sizeof(char));
    printf("Enter expression: ");
    scanf_s("%s", expression);
    int result = stackExpressionCount(expression, amountOfChars);
    printf("Result: %d\n", result);
    free(expression);
}
