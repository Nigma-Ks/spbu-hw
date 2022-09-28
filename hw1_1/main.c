#include <stdio.h>

int main() {
    float x = 0;
    printf("Program can calculate this expression x^4 + x^3 + x^2 + x + 1\n");
    printf("Enter x: "); //x^2(x^2 + x) + x^2 + x + 1
    scanf_s("%f", &x);
    float xSquare = x * x; //first multiplication
    float valueOfExpression = xSquare * (xSquare + x) + xSquare + x + 1; //second multiplication
    printf("Result is %f!", valueOfExpression);
    return 0;
}
