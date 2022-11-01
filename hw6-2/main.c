#include <stdio.h>
#include "cycleList.h"

int safePositionDefiner(int amountOfSoldiers, int killingPeriod) {
    struct CycleList *cycleList = createList();
    for (int i = 1; i <= amountOfSoldiers; i++) {
        push(cycleList, i);
    }
    int currValue = 1;//first position index
    int currValueForRemove = 0;
    while (!oneElementInList(cycleList)) {
        currValue = nextValueWithMStep(cycleList, currValue, killingPeriod);
        currValueForRemove = currValue;
        currValue = nextValueWithMStep(cycleList, currValue, 2); // to get next value in list
        removeByValue(cycleList, currValueForRemove);
        //printList(cycleList);//for check
    }
    int result = getValueOfFirst(cycleList);
    deleteCycleList(cycleList);
    return result;
}

int main() {
    printf("This program shows safe position for soldier if there are n soldiers and\nenemies will kill every m-th "
           "until more than one soldiers stay alive\nEnter n (the amount of soldiers): ");
    int amountOfSoldiers = 0;
    scanf_s("%d", &amountOfSoldiers);
    while (amountOfSoldiers <= 0) {
        printf("Enter n (the amount of soldiers) again: ");
        scanf_s("%d", &amountOfSoldiers);
    }
    printf("Enter m (\"killing period\"): ");
    int killingPeriod = 0;
    scanf_s("%d", &killingPeriod);
    while (killingPeriod <= 0) {
        printf("Enter m (\"killing period\") again: ");
        scanf_s("%d", &killingPeriod);
    }
    int position = safePositionDefiner(amountOfSoldiers, killingPeriod);
    printf("\nPosition: %d\n", position);
    return 0;
}
