#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#define maxLineLen 100
typedef struct {
    char *name;
    char phone[17];
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

PhoneBookEntry* readFile() {
    int amountOfLines = amountOfLinesInFile();
    FILE *phoneBook = fopen("C:\\Users\\Huawei\\Desktop\\HW\\spbu-hw\\hw4-3\\Phone list", "r");
    if (phoneBook == NULL) {
        printf("file not found!");
        return 0;
    }
    PhoneBookEntry *arrayOfPhoneEntries = calloc(amountOfLines, sizeof(PhoneBookEntry));
    fseek(phoneBook, 0, SEEK_SET);
    int linesRead = 0;

    char phone[17] = "";
    char name[maxLineLen - 17] = "";
    while(fscanf(phoneBook, "%s %s", phone, name) != EOF) {
        PhoneBookEntry entry;
        strcpy(entry.phone, phone);
        entry.name = calloc(maxLineLen - 17, sizeof(char));
        strcpy(entry.name, name);
        arrayOfPhoneEntries[linesRead] = entry;
        linesRead++;
    }
    fclose(phoneBook);

    return arrayOfPhoneEntries;
}

void showPhoneBook(PhoneBookEntry *arrayOfPhoneEntries, int len) {
    for (int i = 0; i < len; i++) {
        printf("%s - %s\n", arrayOfPhoneEntries[i].phone, arrayOfPhoneEntries[i].name);
    }
}

void addEntry(char* name, char* phone, PhoneBookEntry* phoneBook, int lines) {
    phoneBook[lines].name = calloc(maxLineLen-17, sizeof(char));
    strcpy(phoneBook[lines].name, name);
    strcpy(phoneBook[lines].phone, phone);
}



void writeToFile(PhoneBookEntry* phoneBook, int lines) {
    FILE *phoneBookFile = fopen("C:\\Users\\Huawei\\Desktop\\HW\\spbu-hw\\hw4-3\\Phone list", "w");
    for (int i = 0; i < lines; i++) {
        fprintf(phoneBookFile, "%s %s", phoneBook[i].phone, phoneBook[i].name);
        fprintf(phoneBookFile, "\n");
    }
    fclose(phoneBookFile);
}
bool findByName(char* name, PhoneBookEntry* phoneBook, int lines) {
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(phoneBook[i].name, name)) {
            printf("\n%s - %s\n", phoneBook[i].phone, phoneBook[i].name);
            found = true;
        }
    }
    return found;
}

bool findByPhone(char* phone, PhoneBookEntry* phoneBook, int lines) {
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(phoneBook[i].phone, phone)) {
            printf("\n%s - %s\n", phoneBook[i].phone, phoneBook[i].name);
            found = true;
        }
    }
    return found;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("В этой программе содержится телефонный справочник. Введите число, соответсвующее желаемому результату\n"
           "0 — выйти\n"
           "1 — добавить запись (имя и телефон)\n"
           "2 — распечатать все имеющиеся записи\n"
           "3 — найти телефон по имени\n"
           "4 — найти имя по телефону\n"
           "5 — сохранить текущие данные в файл\n");
    PhoneBookEntry* phoneBook = calloc(100, sizeof (PhoneBookEntry));
    int len = amountOfLinesInFile();
    memcpy(phoneBook, readFile(), len*sizeof(PhoneBookEntry));

    int choice = -1;
    while (choice != 0) {
        scanf_s("%d", &choice);
        if (choice == 1) {
            printf("add entry:");
            addEntry("sasha", "1111111111111", phoneBook, len);
            len++;
        } else if (choice == 2) {
            showPhoneBook(phoneBook, len);
        } else if (choice == 3) {
            findByPhone("1111111111111", phoneBook, len);
        } else if (choice == 4) {
            findByName("sasha", phoneBook, len);
        } else if (choice == 5) {
            writeToFile(phoneBook, len);
        }
    }
    return 0;
}
