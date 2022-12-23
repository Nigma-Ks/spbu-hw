#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PHONE_LEN 16+1
#define MAX_LINE_LEN 100
#define MAX_NAME_LEN 82
#define FILE_PATH "..\\Phone list.txt"
#define TEST_FILE_PATH "..\\test_phone_list.txt"

typedef struct {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
} PhoneBookEntry;

int amountOfLinesInFile(char *file) {
    FILE *phoneBook = fopen(file, "r");

    if (phoneBook == NULL) {
        return -1;
    }

    int amount = 0;
    char line[MAX_LINE_LEN];
    while (!feof(phoneBook)) {
        if (fgets(line, MAX_LINE_LEN, phoneBook) == NULL) {
            break;
        }
        amount++;
    }
    if (fclose(phoneBook)) {
        printf("dum");
        exit(1);
    }
    return amount;
}

PhoneBookEntry *readFile(int *error, char *file) {
    int amountOfLines = amountOfLinesInFile(file);
    if (amountOfLines == -1) {
        *error = -1;
        return NULL;
    }
    FILE *phoneBookFile = fopen(file, "r");
    if (phoneBookFile == NULL) {
        *error = -1;
        return NULL;
    }
    PhoneBookEntry *arrayOfPhoneEntries = calloc(amountOfLines, sizeof(PhoneBookEntry));
    int linesRead = 0;
    char phone[MAX_PHONE_LEN] = "";
    char name[MAX_NAME_LEN] = "";
    while (fscanf(phoneBookFile, "%s %s", phone, name) != EOF) {
        PhoneBookEntry entry;
        strcpy(entry.phone, phone);
        strcpy(entry.name, name);
        arrayOfPhoneEntries[linesRead] = entry;
        linesRead++;
    }
    fclose(phoneBookFile);

    return arrayOfPhoneEntries;
}

void showPhoneBook(PhoneBookEntry *arrayOfPhoneEntries, int len) {
    for (int i = 0; i < len; i++) {
        printf("%s - %s\n", arrayOfPhoneEntries[i].phone, arrayOfPhoneEntries[i].name);
    }
}

void addEntry(char *name, char *phone, PhoneBookEntry *phoneBook, int *lines) {
    strcpy(phoneBook[*lines].name, name);
    strcpy(phoneBook[*lines].phone, phone);
    (*lines)++;
}

void writeToFile(PhoneBookEntry *phoneBook, int lines, int *error) {
    FILE *phoneBookFile = fopen(FILE_PATH, "w");
    if (phoneBookFile == NULL) {
        *error = -1;
        return;
    }
    for (int i = 0; i < lines; i++) {
        fprintf(phoneBookFile, "%s %s", phoneBook[i].phone, phoneBook[i].name);
        fprintf(phoneBookFile, "\n");
    }
    fclose(phoneBookFile);
}

bool findByName(char *name, PhoneBookEntry *phoneBook, int lines, bool printResult) {
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(phoneBook[i].name, name)) {
            if (!found) {
                if (printResult) {
                    printf("Matching entries:\n");
                }
            }
            if (printResult) {
                printf("%s - %s\n", phoneBook[i].phone, phoneBook[i].name);
            }
            found = true;
        }
    }
    return found;
}

bool findByPhone(char *phone, PhoneBookEntry *phoneBook, int lines, bool printResult) {
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(phoneBook[i].phone, phone)) {
            if (!found) {
                if (printResult) {
                    printf("Matching entries:\n");
                }
            }
            if (printResult) {
                printf("%s - %s\n", phoneBook[i].phone, phoneBook[i].name);
            }
            found = true;
        }
    }
    return found;
}

void showHelpMessage() {
    printf("\nThis is phonebook. Please enter the number of your choice\n"
           "0 - exit\n"
           "1 - add entry (name and phone)\n"
           "2 - print all existing entries\n"
           "3 - find entry by name\n"
           "4 - find entry by phone\n"
           "5 - save phonebook to file\n");
    printf("number>> ");
}

bool testSetupTwoEntries(char *testFileName, PhoneBookEntry **pb, int *len) {
    FILE *file = fopen(testFileName, "a+");
    if (file == NULL) {
        return false;
    }
    fprintf(file, "7890 ksu\n765432 max\n");
    if (fclose(file)) {
        return false;
    }
    int error = 0;
    *pb = calloc(100, sizeof(PhoneBookEntry));
    PhoneBookEntry *baseOfPhoneEntries = NULL;
    baseOfPhoneEntries = readFile(&error, testFileName);
    if (error) {
        return false;
    }
    *len = amountOfLinesInFile(testFileName);
    memcpy(*pb, baseOfPhoneEntries, *len * sizeof(PhoneBookEntry));
    free(baseOfPhoneEntries);
    return true;
}

bool testEntryAddition() {
    char *testName = "test_name";
    char *testPhone = "test_phone";
    PhoneBookEntry *testPhoneBook = NULL;

    int len = 0;
    if (!testSetupTwoEntries(TEST_FILE_PATH, &testPhoneBook, &len)) {
        return false;
    }
    int oldLen = len;
    addEntry(testName, testPhone, testPhoneBook, &len);

    return !strcmp(testPhoneBook[len - 1].name, testName) && !strcmp(testPhoneBook[len - 1].phone, testPhone) &&
           oldLen + 1 == len;
}

bool testFindByPhoneIfPhoneExists() {
    PhoneBookEntry *testPhoneBook = NULL;
    int len = 0;
    if (!testSetupTwoEntries(TEST_FILE_PATH, &testPhoneBook, &len)) {
        return false;
    }

    if (!findByPhone("7890", testPhoneBook, len, false)) {
        free(testPhoneBook);
        remove(TEST_FILE_PATH);
        return false;
    }

    free(testPhoneBook);
    remove(TEST_FILE_PATH);
    return true;
}

bool testFindByNameIfNameExists() {
    PhoneBookEntry *testPhoneBook = NULL;
    int len = 0;
    if (!testSetupTwoEntries(TEST_FILE_PATH, &testPhoneBook, &len)) {
        return false;
    }

    if (!findByName("max", testPhoneBook, len, false)) {
        free(testPhoneBook);
        remove(TEST_FILE_PATH);
        return false;
    }

    free(testPhoneBook);
    remove(TEST_FILE_PATH);
    return true;
}

bool testFindByNameIfNameNotExists() {
    PhoneBookEntry *testPhoneBook = NULL;
    int len = 0;
    if (!testSetupTwoEntries(TEST_FILE_PATH, &testPhoneBook, &len)) {
        return false;
    }

    if (findByName("NOT_EXISTING_NAME", testPhoneBook, len, false)) {
        free(testPhoneBook);
        remove(TEST_FILE_PATH);
        return false;
    }

    free(testPhoneBook);
    remove(TEST_FILE_PATH);
    return true;
}

bool performTests() {
    return testFindByNameIfNameExists() && testFindByNameIfNameNotExists() && testFindByPhoneIfPhoneExists() &&
           testEntryAddition();
}

int main() {
    if (performTests()) {
        printf("Tests were passed!\n");
    } else {
        printf("Tests were not passed!\n");
        return 0;
    }
    int error = 0;
    FILE *phoneBookFile = fopen(FILE_PATH, "r");
    if (phoneBookFile == NULL) {
        phoneBookFile = fopen(FILE_PATH, "a+");
    }
    fclose(phoneBookFile);
    PhoneBookEntry *phoneBook = calloc(100, sizeof(PhoneBookEntry));

    if (phoneBook == NULL) {
        printf("Memory allocation error\n");
        return 0;
    }

    int len = amountOfLinesInFile(FILE_PATH);

    if (len == -1) {
        free(phoneBook);
        printf("No file\n");
        return 0;
    }
    PhoneBookEntry *baseOfPhoneEntries = NULL;
    baseOfPhoneEntries = readFile(&error, FILE_PATH);
    memcpy(phoneBook, baseOfPhoneEntries, len * sizeof(PhoneBookEntry));
    free(baseOfPhoneEntries);
    if (error) {
        free(phoneBook);
        printf("No file\n");
        return 0;
    }

    int choice = -1;
    while (choice != 0) {
        showHelpMessage();
        scanf_s("%d", &choice);
        if (choice == 1) {
            char *name = calloc(MAX_NAME_LEN, sizeof(char));
            char *phone = calloc(MAX_PHONE_LEN, sizeof(char));
            printf("enter entry name: ");
            scanf("%s", name);
            printf("enter entry phone: ");
            scanf("%s", phone);
            addEntry(name, phone, phoneBook, &len);
            free(name);
            free(phone);
        } else if (choice == 2) {
            printf("your phonebook: \n");
            showPhoneBook(phoneBook, len);
        } else if (choice == 4) {
            char *phone = calloc(MAX_PHONE_LEN, sizeof(char));
            printf("enter searched phone: ");
            scanf("%s", phone);
            if (!findByPhone(phone, phoneBook, len, true)) {
                printf("no such entries!\n");
            }
            free(phone);
        } else if (choice == 3) {
            char *name = calloc(MAX_NAME_LEN, sizeof(char));
            printf("enter searched name: ");
            scanf("%s", name);
            if (!findByName(name, phoneBook, len, true)) {
                printf("no such entries!\n");
            }
            free(name);
        } else if (choice == 5) {
            writeToFile(phoneBook, len, &error);
            if (error) {
                free(phoneBook);
                printf("No file\n");
                return 0;
            }
            printf("your entries now are saved\n");
        }
    }
    free(phoneBook);
    return 0;
}
