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

PhoneBookEntry * readFile() {
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

void writeToFile(char* name, char* phone) {
    int amountOfLines = amountOfLinesInFile();
    FILE *phoneBook = fopen("C:\\Users\\Huawei\\Desktop\\HW\\spbu-hw\\hw4-3\\Phone list", "a");
    fprintf(phoneBook, "%s %s", phone, name);
    fprintf(phoneBook, "\n");
}
bool findByName(char* name) {
    PhoneBookEntry* currPhoneBook = readFile();
    int lines = amountOfLinesInFile();
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(currPhoneBook[i].name, name)) {
            printf("\n%s - %s\n", currPhoneBook[i].phone, currPhoneBook[i].name);
            found = true;
        }
    }
    return found;
}

bool findByPhone(char* phone) {
    PhoneBookEntry* currPhoneBook = readFile();
    int lines = amountOfLinesInFile();
    bool found = false;
    for (int i = 0; i < lines; i++) {
        if (!strcmp(currPhoneBook[i].phone, phone)) {
            printf("\n%s - %s\n", currPhoneBook[i].phone, currPhoneBook[i].name);
            found = true;
        }
    }
    return found;
}


int main() {
    PhoneBookEntry* pbe = readFile();
    int lines = amountOfLinesInFile();
    writeToFile("sasha", "1111111111111");

    showPhoneBook(pbe, lines);

    printf("%d", findByName("ksu"));
    printf("%d", findByPhone("0000000000000000"));
    printf("%d", findByName("k1su"));


}
int main1() {
    SetConsoleOutputCP(CP_UTF8);
    printf("В этой программе содержится телефонный справочник. Введите число, соответсвующее желаемому результату\n"
           "0 — выйти\n"
           "1 — добавить запись (имя и телефон)\n"
           "2 — распечатать все имеющиеся записи\n"
           "3 — найти телефон по имени\n"
           "4 — найти имя по телефону\n"
           "5 — сохранить текущие данные в файл\n");
    int choice = -1;
    while (choice != 0) {
        scanf_s("%d", &choice);
        if (choice == 1) {
            printf()
        } else if (choice == 2) {

        } else if (choice == 3) {

        } else if (choice == 4) {

        } else if (choice == 5) {

        }
    }
    return 0;
}
