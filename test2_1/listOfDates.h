#pragma once

struct ListElement;

struct List;

struct List *createList();

int listLen(struct List *list);

int insert(struct List *list, int day, int month, int year);

int printList(struct List *list);

int getValueByIndex(struct List *list, int index, int *day, int *month, int *year);

int deleteList(struct List *list);

