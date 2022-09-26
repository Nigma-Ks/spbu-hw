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
    scanf_s("%s", s1);
    if (strlen(s1) > strlen(s)){
        printf("There isn't s1 in s");
        return 0;
    }
    int counterSubstr = 0;
    bool isSubstrIn = true;
    for (int i = 0; i <= strlen(s) - strlen(s1); i++) {
        for (int j = 0; j < strlen(s1); j++){
            if (s[i+j] != s1[j]){
                isSubstrIn = false;
                break;
            }
        }
        if (isSubstrIn) counterSubstr++;
        isSubstrIn = true;
    }
    if (counterSubstr == 0){
        printf("There isn't s1 in s");
    }else if (counterSubstr == 1){
        printf("There is one s1 in s");
    }else{
        printf("There are %d s1 in s", counterSubstr);
    }
    return 0;
}
