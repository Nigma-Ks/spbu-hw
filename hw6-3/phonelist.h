#pragma once

struct PhoneListElement;

struct PhoneList;

struct PhoneList *createList();

int listLen(struct PhoneList *phoneList);

int insert(struct PhoneList *phoneList, char *name, char *phone);

struct PhoneList *createSubList(struct PhoneList *phoneList, int startIndex, int finishIndex, int *error);

int printList(struct PhoneList *phoneList);

int changeElementValueByIndex(struct PhoneList *phoneList, int index, char *newName, char *newPhone);

int getValueByIndex(struct PhoneList *phoneList, int index, char *name, char *phone);

int deleteList(struct PhoneList *phoneList);

