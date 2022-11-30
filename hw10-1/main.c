#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLEN 1000
#define PATH "..//graph.txt"

void addToStatesCities(int **states, int nearestToCapitalCity, int size, int capitalIndex) {
    for (int i = 0; i < size; i++) {
        if (states[capitalIndex][i] == 0) {
            if (nearestToCapitalCity == 0) {
                nearestToCapitalCity = -1;
            }
            states[capitalIndex][i] = nearestToCapitalCity;
            return;
        }
    }
}

void deleteRoadsToCity(int **graph, int nearestToCapitalCity, int size) {
    for (int i = 0; i < size; i++) {
        graph[i][nearestToCapitalCity] = 0;
    }
}

void lengthenRoadsFromCity(int **graph, int nearestToCapitalCity, int roadToNearest, int size) {
    for (int i = 0; i < size; i++) {
        if (graph[nearestToCapitalCity][i]) {
            graph[nearestToCapitalCity][i] += roadToNearest;
        }
    }
}

int notZeroMinimum(const int *array, int size, int *nearestToCurrCity) {
    int minimum = MAXLEN;
    for (int i = 0; i < size; i++) {
        if (array[i] < minimum && array[i] != 0) {
            minimum = array[i];
            *nearestToCurrCity = i;
        }
    }
    if (minimum != MAXLEN) {
        return minimum;
    }
    return 0;
}

void printGraph(int **graph, int columns, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void printResult(int **graph, int columns, int rows) {
    for (int i = 0; i < rows; i++) {
        printf("\nState number %d: ", i + 1);
        for (int j = 0; j < columns; j++) {
            if (graph[i][j] == -1) {
                printf("0 ");
            } else if (graph[i][j] == 0) {
                break;
            } else {
                printf("%d ", graph[i][j]);
            }
        }
    }
    printf("\n");
}

void cityDistribution(int **graph, int **states, int amountOfCities, int amountOfCapitals) {
    int usedCities = 0;
    while (usedCities < amountOfCities - 2) { //because two cities already in states
        for (int capitalIndex = 0; capitalIndex < amountOfCapitals; capitalIndex++) {
            int prevCityOfCapital = 0;
            int nearestToCapitalCity = 0;
            int roadToNearest = MAXLEN;
            for (int townOfState = 0; townOfState < amountOfCities; townOfState++) { //cycle of cities in state
                if (states[capitalIndex][townOfState] != 0) {
                    int nearestToCurrCity = 0;
                    int currLen = 0;
                    if (states[capitalIndex][townOfState] == -1) { //0-stop-symbol, -1 means index 0
                        currLen = notZeroMinimum(graph[0], amountOfCities,
                                                 &nearestToCurrCity); //min len in -1 case
                    } else {
                        currLen = notZeroMinimum(graph[states[capitalIndex][townOfState]], amountOfCities,
                                                 &nearestToCurrCity); //min len
                    }
                    if (currLen != 0) {
                        if (currLen < roadToNearest) {
                            roadToNearest = currLen;
                            nearestToCapitalCity = nearestToCurrCity;
                            prevCityOfCapital = states[capitalIndex][townOfState]; //for deleting path from previous to not return again
                            if (states[capitalIndex][townOfState] == -1) {
                                prevCityOfCapital = 0;
                            }
                        }
                    }
                } else {
                    break;
                }
            }
            if (roadToNearest != MAXLEN) {
                graph[nearestToCapitalCity][prevCityOfCapital] = 0; //deleting path from previous to not return again
                deleteRoadsToCity(graph, nearestToCapitalCity, amountOfCities); //deleting way to city for other states
                lengthenRoadsFromCity(graph, nearestToCapitalCity, roadToNearest,
                                      amountOfCities); //can go there only from states' cities
                addToStatesCities(states, nearestToCapitalCity, amountOfCities, capitalIndex);
                usedCities++;
            }
        }
    }
}

int **arrayOfStatesWithCities(int *nCities, int *nCapitals, bool *noFile) {
    FILE *file = fopen(PATH, "r");
    if (file == NULL) {
        *noFile = true;
        return NULL;
    }
    int amountOfCities = 0;
    int amountOfRoads = 0;
    int amountOfCapitals = 0;
    if (fscanf_s(file, "%d", &amountOfCities) == EOF) {
        return NULL;
    }
    fscanf_s(file, "%d", &amountOfRoads);
    int **graph = (int **) calloc(amountOfCities, sizeof(*graph));
    for (int i = 0; i < amountOfCities; i++) {
        graph[i] = (int *) calloc(amountOfCities, sizeof(*graph[i]));
    }
    for (int i = 0; i < amountOfRoads; i++) {
        int fstCity = 0;
        int sndCity = 0;
        int roadLen = 0;
        fscanf_s(file, "%d", &fstCity);
        fscanf_s(file, "%d", &sndCity);
        fscanf_s(file, "%d", &roadLen);
        graph[fstCity][sndCity] = roadLen;
        graph[sndCity][fstCity] = roadLen;
    }
    fscanf_s(file, "%d", &amountOfCapitals);
    *nCities = amountOfCities;
    *nCapitals = amountOfCapitals;
    int **states = (int **) calloc(amountOfCapitals, sizeof(*states));
    for (int i = 0; i < amountOfCapitals; i++) {
        states[i] = (int *) calloc(amountOfCities, sizeof(*states[i]));
    }
    printGraph(graph, amountOfCities, amountOfCities);
    for (int i = 0; i < amountOfCapitals; i++) {
        int capitalNumber = 0;
        fscanf_s(file, "%d", &capitalNumber);
        deleteRoadsToCity(graph, capitalNumber, amountOfCities);
        states[i][0] = capitalNumber;
    }
    cityDistribution(graph, states, amountOfCities, amountOfCapitals);
    for (int i = 0; i < amountOfCities; i++) {
        free(graph[i]);
    }
    free(graph);
    fclose(file);
    return states;
}

int main() {
    printf("This program distributes cities in file across states\n\n");
    bool noFile = false;
    int amountOfCities = 0;
    int amountOfCapitals = 0;
    int **states = arrayOfStatesWithCities(&amountOfCities, &amountOfCapitals, &noFile);
    if (noFile) {
        printf("File wasn't found!");
        return 0;
    }
    if (states == NULL) {
        printf("Nothing in file");
        return 0;
    }
    printResult(states, amountOfCities, amountOfCapitals);
    for (int i = 0; i < amountOfCities; i++) {
        free(states[i]);
    }
    free(states);
    printf("\n");
    return 0;
}
