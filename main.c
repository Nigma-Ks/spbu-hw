#include <stdio.h>


unsigned long nFibonacciMemberRecursive(int numberInSequence) {
    if (numberInSequence < 3) return 1;
    return nFibonacciMemberRecursive(numberInSequence - 1)
           + nFibonacciMemberRecursive(numberInSequence - 2);
}

unsigned long nFibonacciMemberIterative(int numberInSequence) {
    if (numberInSequence < 3) return 1;
    unsigned long nMinusTwoElementInSequence = 0, nMinusOneElementInSequence = 1, nElementInSequence = 1;
    for (int indexInFibonacci = 3; indexInFibonacci <= numberInSequence; indexInFibonacci++) {
        nMinusTwoElementInSequence = nMinusOneElementInSequence;
        nMinusOneElementInSequence = nElementInSequence;
        nElementInSequence = nMinusTwoElementInSequence + nMinusOneElementInSequence;
    }
    return nElementInSequence;
}


int main() {
    printf("This program calculates n-member(n is a natural number) of the Fibonacci sequence\nEnter n: ");
    int numberInSequence = 0;
    scanf_s("%d", &numberInSequence);
    while (numberInSequence <= 0) {
        printf("Numbers of members start from 1, try again\nEnter n: ");
        scanf_s("%d", &numberInSequence);
    }
    printf("How do you want to calculate? By recursive function or iterative?\nEnter '1' if recursive or '2' if iterative: ");
    int choiceOfCalculatingMethod = 0;
    scanf_s("%d", &choiceOfCalculatingMethod);
    while (!(choiceOfCalculatingMethod == 1 || choiceOfCalculatingMethod == 2)) {
        printf("You can enter only '1' or '2', try again\nEnter '1' if recursive or '2' if iterative: ");
        scanf_s("%d", &choiceOfCalculatingMethod);
    }
    if (choiceOfCalculatingMethod == 1) {
        printf("%d member in Fibonacci sequence is %lu!\n", numberInSequence,
               nFibonacciMemberRecursive(numberInSequence));
        return 0;
    }
    printf("%d member in Fibonacci sequence is %lu!\n", numberInSequence,
           nFibonacciMemberIterative(numberInSequence));
    return 0;
}
