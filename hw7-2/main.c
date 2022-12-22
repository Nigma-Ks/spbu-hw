#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "arithmeticTree.h"

#define maxBufferLen 100
#define filePath "..\\expression.txt"

typedef enum Error {
    noElement,
    memoryAllocationError,
    OK
} Error;

int main() {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return -1;
    }
    char *expression = calloc(maxBufferLen, sizeof(char));
    fgets(expression, maxBufferLen, file);
    printf("This program calculates expression in file\n");
    printf("Expression in file: %s\n", expression);
    int result = 0;
    struct StackTail *stack = create(&result);
    struct ArithmeticTree *arithmeticTree = NULL;
    struct ArithmeticTreeElement *curr = NULL;
    bool isLeft = true;
    addNewWithCurrKnotLink(&arithmeticTree, &curr, isLeft);
    for (int i = 0; i < strlen(expression); i++) {
        if (((int) expression[i] - 48) >= 0 && ((int) expression[i] - 48) <= 9) {
            int p = 0;
            while (((int) expression[i] - 48) >= 0 && ((int) expression[i] - 48) <= 9) {
                p = p * 10 + ((int) expression[i] - 48);
                i++;//when cycle will be over expression[i] = ' ' or ')' or i will be too big
            }
            assignValueCurr(&curr, p, '\0');
            if (!isEmpty(stack)) {
                pop(stack, &curr);
                addNewWithCurrKnotLink(&arithmeticTree, &curr, false);
            }
        }
        if (expression[i] == '(') {
            assignValueCurr(&curr, 0, expression[i + 1]);
            push(stack, curr);
            addNewWithCurrKnotLink(&arithmeticTree, &curr, true);
            i++;
        }
    }
    printf("\nExpression after algorithm processing: ");
    printTree(arithmeticTree);
    printf("\nResult is %d\n", treeResult(arithmeticTree));
    deleteTree(arithmeticTree);
    free(stack);
    fclose(file);
}
