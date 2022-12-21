#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LEN 200
#define START_STATE 0
#define ACCEPTING_STATE 1
#define FAIL_STATE 2

bool isLetter(char symbol) {
    return symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z';
}

bool isDigit(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

void move(char symbol, int *state) {
    switch (*state) {
        case START_STATE:
            if (isLetter(symbol)) {
                *state = ACCEPTING_STATE;
            } else {
                *state = FAIL_STATE;
            }
            break;
        case ACCEPTING_STATE:
            if (isDigit(symbol) || isLetter(symbol) || symbol == '_') {
                *state = ACCEPTING_STATE;
            } else {
                *state = FAIL_STATE;
            }
            break;
        case FAIL_STATE:
            break;
    }
}

bool DFA(char *word, int lenOfWord) {
    int state = START_STATE;
    for (int i = 0; i < lenOfWord; i++) {
        move(word[i], &state);
    }
    return state == ACCEPTING_STATE;
}

int main() {
    printf("This program is realisation of deterministic finite automaton\n"
           "that accepts words = [A-Za-z] ([A-Za-z] | [0-9] | _ )* with 200 or less symbols\n");
    char word[MAX_WORD_LEN + 1] = {0};
    printf("Enter your word: ");
    scanf_s("%200s", word);
    int lenOfWord = (int) strlen(word);
    bool wordIsAcceptedByDFA = DFA(word, lenOfWord);
    if (wordIsAcceptedByDFA) {
        printf("Word is accepted by DFA!\n");
        return 0;
    }
    printf("Word isn't accepted by DFA!\n");
    return 0;
}
