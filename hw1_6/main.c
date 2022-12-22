#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    printf("This program can count how many strings = s1 are in another string s\n");
    char s[200] = "";
    char s1[100] = "";
    printf("Enter s (only 100 chars and less): ");
    scanf_s("%s", s);
    printf("Enter s1 (only 100 chars and less): ");
    scanf_s("%s", s1); //strlen() returns unsigned int, but s and s1 contains less than 101 chars
    int lenSMinusLenS1 = strlen(s) - strlen(s1), lenS1 = strlen(s1), lenS = strlen(s);
    if (lenS1 > lenS) {
        printf("There isn't s1 in s\n");
        return 0;
    }
    int counterSubstr = 0;
    bool isSubstrIn = true;
    for (int i = 0; i <= lenSMinusLenS1; i++) {
        for (int j = 0; j < lenS1; j++) {
            if (s[i + j] != s1[j]) {
                isSubstrIn = false;
                break;
            }
        }
        if (isSubstrIn) counterSubstr++;
        isSubstrIn = true;
    }
    if (counterSubstr == 0) {
        printf("There isn't s1 in s\n");
    } else if (counterSubstr == 1) {
        printf("There is one s1 in s\n");
    } else {
        printf("There are %d s1 in s\n", counterSubstr);
    }
    return 0;
}
