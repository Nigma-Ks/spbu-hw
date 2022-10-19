#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#define maxPhoneLen 16+1
#define maxLineLen 100
typedef struct {
    char *name;
    char phone[maxPhoneLen];
} PhoneBookEntry;

int amountOfLinesInFile() {
    FILE *phoneBook = fopen("C:\\Users\\Huawei\\Desktop\\HW\\spbu-hw\\hw4-3\\Phone list", "r");
    int amount = 0;
    char line[maxLineLen];
    fseek(phoneBook, 0, SEEK_SET);
    while (!feof(phoneBook)) {
        if (fgets(line, maxLineLen, phoneBook) == NULL) {
            break;
        }
        amount++;
    }
    fclose(phoneBook);
    return amount;
}

PhoneBookEntry *readFile() {
    int amountOfLines = amountOfLinesInFile();
    FILE *phoneBook = fopen("C:\\Users\\Huawei\\Desktop\\HW\\spbu-hw\\hw4-3\\Phone list", "r");
    if (phoneBook == NULL) {
        printf("file not found!");
        return 0;
    }
    PhoneBookEntry *arrayOfPhoneEntries = calloc(amountOfLines, sizeof(PhoneBookEntry));
    fseek(phoneBook, 0, SEEK_SET);
    int linesRead = 0;

    char phone[maxPhoneLen] = "";
    char name[maxLineLen - maxPhoneLen] = "";
    while (fscanf(phoneBook, "%s %s", phone, name) != EOF) {
        PhoneBookEntry entry;
        strcpy(entry.phone, phone);
        entry.name = calloc(maxLineLen - maxPhoneLen, sizeof(char));
        strcpy(entry.name, name);
        arrayOfPhoneEntries[linesRead] = entry;
        linesRead++;
        //free(entry.name);
        //free(entry.phone);
    }
    fclose(phoneBook);

    return arrayOfPhoneEntries;
}

void showPhoneBook(PhoneBookEntry *arrayOfPhoneEntries, int len) {
    for (int i = 0; i < len; i++) {
        printf("%s - %s\n", arrayOfPhoneEntries[i].phone, arrayOfPhoneEntries[i].name);
    }
}

void addEntry(char *name, char *phone, PhoneBookEntry *phoneBook, int lines) {
    phoneBook[lines].name = calloc(maxLineLen - maxPhoneLen, sizeof(char));
    strcpy(phoneBook[lines].name, name);
    strcpy(phoneBook[lines].phone, phone);
}


void writeToFile(PhoneBookEntry *phoneBook, int lines) {
    FILE *phoneBookFile = fopen("C:\\Users\\Huawei\\Desktop\\HW\\spbu-hw\\hw4-3\\Phone list", "w");
    for (int i = 0; i < lines; i++) {
        fprintf(phoneBookFile, "%s %s", phoneBook[i].phone, phoneBook[i].name);
        fprintf(phoneBookFile, "\n");
    }
    fclose(phoneBookFile);
}

bool findByName(char *name, PhoneBookEntry *phoneBook, int lines) {
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(phoneBook[i].name, name)) {
            if (!found) {
                printf("Matching entries:\n");
            }
            printf("%s - %s\n", phoneBook[i].phone, phoneBook[i].name);
            found = true;
        }
    }
    return found;
}

bool findByPhone(char *phone, PhoneBookEntry *phoneBook, int lines) {
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(phoneBook[i].phone, phone)) {
            if (!found) {
                printf("Matching entries:\n");
            }
            printf("%s - %s\n", phoneBook[i].phone, phoneBook[i].name);
            found = true;
        }
    }
    return found;
}

void showMenu() {
    printf("\nThis is phonebook. Please enter the number of your choice\n"
           "0 — exit\n"
           "1 — add entry (name and phone)\n"
           "2 — print all existing etries\n"
           "3 — find entry by name\n"
           "4 — find entry by phone\n"
           "5 — save phonebook to file\n");
    printf("number>> ");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    PhoneBookEntry *phoneBook = calloc(100, sizeof(PhoneBookEntry));
    int len = amountOfLinesInFile();
    PhoneBookEntry *baseOfPhoneEntries = readFile();
    memcpy(phoneBook, baseOfPhoneEntries, len * sizeof(PhoneBookEntry));
    free(baseOfPhoneEntries);
    int choice = -1;
    while (choice != 0) {
        showMenu();

        scanf_s("%d", &choice);
        if (choice == 1) {
            char *name = calloc(maxLineLen - maxPhoneLen, sizeof(char));
            char *phone = calloc(maxPhoneLen, sizeof(char));
            printf("enter entry name: ");
            scanf("%s", name);
            printf("enter entry phone: ");
            scanf("%s", phone);
            addEntry(name, phone, phoneBook, len);
            len++;
            free(name);
            free(phone);
        } else if (choice == 2) {
            printf("your phonebook: \n");
            showPhoneBook(phoneBook, len);
        } else if (choice == 4) {
            char *phone = calloc(maxPhoneLen, sizeof(char));
            printf("enter searched phone: ");
            scanf("%s", phone);
            if (!findByPhone(phone, phoneBook, len)) {
                printf("no such entries!\n");
            }
            free(phone);
        } else if (choice == 3) {
            char *name = calloc(maxLineLen - maxPhoneLen, sizeof(char));
            printf("enter searched name: ");
            scanf("%s", name);
            if (!findByName(name, phoneBook, len)) {
                printf("no such entries!\n");
            }
            free(name);
        } else if (choice == 5) {
            writeToFile(phoneBook, len);
            printf("your entries now are saved\n");
        }
    }
    free(phoneBook);
    return 0;
}

