#pragma once

struct CycleListElement;

struct CycleList;

struct CycleList *createList();

int push(struct CycleList *cycleList, int value); //adds new value, return -2 if no list -1 if !calloc 0 if success

int removeByValue(struct CycleList *cycleList, int value); //removes value, returns -2 if no list, -3 if there
// isn't such value or 0 if success

int oneElementInList(struct CycleList *cycleList); //-2 if no list or result of logic expression

int deleteCycleList(struct CycleList *cycleList); //-2 if no list or 0

int getValueOfFirst(struct CycleList *cycleList); //returns -2 if no list or first value

int nextValueWithMStep(struct CycleList *cycleList, int currValue, int m);//-2, -1 if there is no or one element
// or value m-th from current

int printList(struct CycleList *cycleList); //prints list, -2, 0