#pragma once

struct SortedListElement;

struct SortedList;

struct SortedList *create();//creates empty sorted list

int insert(struct SortedList *sortedList, int value);//adds new element on the right place in list,
// returns -2 if there is no sorted list, -1 if calloc returned NULL

int removeValue(struct SortedList *sortedList, int index, int *value);

int printList(struct SortedList *sortedList);// prints sorted list, returns -2 if there is no sorted list

void deleteList(struct SortedList *sortedList);//deletes all elements in sorted list and sorted list