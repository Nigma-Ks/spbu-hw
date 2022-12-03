#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN INT_MAX
#define PATH "..//graph.txt"

void addCityToState(int **states, int nearestToCapitalCity, int size, int capitalIndex) {
    for (int i = 0; i < size; i++) {
        if (states[capitalIndex][i] == -1) {
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

int minExistingPath(const int *array, int size, int *nearestToCurrCity) {
    int minimum = MAX_LEN;
    for (int i = 0; i < size; i++) {
        if (array[i] < minimum && array[i] != 0) {
            minimum = array[i];
            *nearestToCurrCity = i;
        }
    }
    if (minimum != MAX_LEN) {
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
    int amountOfCitiesToDistribute = amountOfCities - amountOfCapitals;
    while (usedCities < amountOfCitiesToDistribute) { //because capital cities already in states
        for (int capitalIndex = 0; capitalIndex < amountOfCapitals; capitalIndex++) {
            int parentCity = 0;
            int nearestCity = 0;
            int roadToNearestCityLen = MAX_LEN;
            for (int townOfStateIndex = 0;
                 townOfStateIndex < amountOfCities; townOfStateIndex++) { //cycle of cities in state
                int townOfState = states[capitalIndex][townOfStateIndex];
                if (townOfState == -1) {
                    break; // if state towns exhausted
                }
                int nearestToCurrCity = 0;
                int currLen = minExistingPath(graph[townOfState], amountOfCities, &nearestToCurrCity);
                if (currLen != 0) { // if path exists
                    if (currLen < roadToNearestCityLen) {
                        roadToNearestCityLen = currLen;
                        nearestCity = nearestToCurrCity;
                        parentCity = townOfState; //for deleting path from previous to not return again
                    }
                }
            }

            if (roadToNearestCityLen != MAX_LEN) {
                graph[nearestCity][parentCity] = 0; //deleting path to previous for not returning again
                deleteRoadsToCity(graph, nearestCity, amountOfCities); //deleting way to city for other states
                addCityToState(states, nearestCity, amountOfCities, capitalIndex);
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
        for (int j = 0; j < amountOfCities; j++) {
            states[i][j] = -1;
        }
    }
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

