#include <stdio.h>
#include <stdlib.h>

int main() {
    int dividend = 0, divider = 0, positiveIncompleteQuotient = 0, answerSign = 1;
    printf("Enter dividend: ");
    scanf_s("%d", &dividend);
    printf("Enter divider(do not enter zero): ");
    scanf_s("%d", &divider);
    while (divider == 0){
        printf("Zero can not be divider, try again\n");
        printf("Enter divider(do not enter zero): ");
        scanf_s("%d", &divider);
    }
    if (((dividend < 0)||(divider < 0)) && !((dividend < 0) && (divider < 0))){
        answerSign = -1;
        divider = -divider; //if dividend < 0 we can change signs positiveIncompleteQuotient and divider and answer will be the same but positive
        // if divider < 0 we can delete minuses divider and positiveIncompleteQuotient and answer will be the same but positive
    }
    while ((dividend - divider * positiveIncompleteQuotient < 0) || (dividend - divider * positiveIncompleteQuotient >=
    abs(divider))) {
        positiveIncompleteQuotient++;
    }
    printf("Incomplete quotient is %d", positiveIncompleteQuotient * answerSign);
    return 0;
}
