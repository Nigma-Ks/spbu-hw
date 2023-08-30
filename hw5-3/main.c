#include <stdio.h>
#include "stack.h"

int isSndLessPriority(char operator1, char operator2) {
    if (((operator2 == '+') || (operator2 == '-')) && ((operator1 == '*') || (operator1 == '/'))) {
        return 1;
    }
    return 0;
}

int isOperator(char operator) {
    return (operator == '+') || (operator == '-') || (operator == '*') || (operator == '/');
}

int fromInfixToReversedPolishTransform(const char *expression, int expressionLen, char *result) {
    int resultStackCreation = 0;
    StackTail *stack = create(&resultStackCreation);
    int indexResultString = 0;
    for (int i = 0; i < expressionLen; i++) {
        if ((int) expression[i] >= 48 && (int) expression[i] <= 57) {
            result[indexResultString] = expression[i];
            indexResultString++;
        } else if (expression[i] == '(') {
            push(stack, expression[i]);
        } else if (expression[i] == ')') {
            if (isEmpty(stack)) {
                return 1;
            }
            char currStack = '\0';
            tailValue(stack, &currStack);
            while (currStack != '(') {
                result[indexResultString] = currStack;
                pop(stack, &currStack);
                if (isEmpty(stack)) {
                    return 1;
                }
                tailValue(stack, &currStack);
                indexResultString++;
            }
            pop(stack, &currStack);
        } else {
            if (!isEmpty(stack)) {
                char currOperator = '\0';
                tailValue(stack, &currOperator);
                while (!isSndLessPriority(expression[i], currOperator) && isOperator(currOperator)) {
                    result[indexResultString] = currOperator;
                    indexResultString++;
                    pop(stack, &currOperator);
                    if (isEmpty(stack)) {
                        break;
                    }
                    tailValue(stack, &currOperator);
                }
            }
            push(stack, expression[i]);
        }
    }
    while (!isEmpty(stack)) {
        char currStack = '\0';
        pop(stack, &currStack);
        if (currStack == '(') return 1;
        result[indexResultString] = currStack;
        indexResultString++;
    }
    return 0;
}

int main() {
    printf("Enter arithmetic infix expression and how many chars are there.\nAmount of chars in expression: ");
    int amountOfChars = 0;
    scanf_s("%d", &amountOfChars);
    char *expression = calloc(amountOfChars, sizeof(char));
    char *result = calloc(amountOfChars, sizeof(char));
    printf("Enter expression: ");
    scanf_s("%s", expression);
    if (!fromInfixToReversedPolishTransform(expression, amountOfChars, result)) {
        printf("Result: %s\n", result);
        free(expression);
        free(result);
        return 0;
    }
    free(expression);
    free(result);
    printf("String is not correct\n");
}
