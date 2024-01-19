#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include <string.h>
#include "cache.h"

int main() {
    Cache cacheData[MAX_CACHES];
    int numCachesLoaded = 0;
    char filename[50]; // Variável para armazenar o nome do ficheiro a ser carregado

    int running = 1;
    char command[20];

    while (running) {
        printf("\n\n\t\t ============== Geo Caching ==============");
        printf("\n\t\t ============== Main Menu ================");
        printf("\n\t\t =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        printf("\n\n\t\t | [1] - Load    |");
        printf("\n\n\t\t | [2] - Clear   |");
        printf("\n\n\t\t | [3] - Quit    |");
        printf("\n\n\t\t | [4] - List    |");
        printf("\n\n\t\t | [5] - FoundP  |");
        printf("\n\n\t\t | [6] - Search  |");
        printf("\n\n\t\t | [7] - Edit    |");
        printf("\n\n\t\t | [8] - Center  |");
        printf("\n\n\t\t | [9] - Age     |");
        printf("\n\n\t\t | [10] - Sort   |");
        printf("\n\n\t\t | [11] - Statec |");
        printf("\n\n\t\t | [12] - M81    |");
        printf("\n\n\t\t | [13] - Save   |");
        printf("\n\n\t\t\t =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        printf("\n\n\t\tEnter a command: ");
        scanf("%s", command);

        // Switch case para lidar com diferentes comandos
        if (strcmp(command, "LOAD") == 0 || strcmp(command, "load") == 0 || strcmp(command, "1") == 0) {
            printf("Enter file name: ");
            scanf("%s", filename);
            loadCachesFromFile(cacheData, &numCachesLoaded, filename);
        } else if (strcmp(command, "CLEAR") == 0 || strcmp(command, "clear") == 0 || strcmp(command, "2") == 0) {
            clearCacheData(cacheData, &numCachesLoaded);
        } else if (strcmp(command, "QUIT") == 0 || strcmp(command, "quit") == 0 || strcmp(command, "3") == 0) {
            running = 0;
        } else if (strcmp(command, "LIST") == 0 || strcmp(command, "list") == 0 || strcmp(command, "4") == 0) {
           if (numCachesLoaded == 0) {
            printf("<No cache data>\n");
        } else {
            printf("List of loaded caches:\n");
            printf("------------------------------------------------------------\n");
            printf("| Code | Name | State | Owner | Latitude | Longitude | Kind | Size | Difficulty | Terrain | Status | Hidden Date | Founds | Not Founds | Favourites | Altitude |\n");
            printf("------------------------------------------------------------\n");
            for (int i = 0; i < numCachesLoaded; i++) {
                displayCache(cacheData[i]);
            }
            printf("------------------------------------------------------------\n");
        }
        } else if (strcmp(command, "FOUNDP") == 0 || strcmp(command, "foundp") == 0 || strcmp(command, "5") == 0) {
            if (numCachesLoaded == 0) {
            printf("<No cache data>\n");
        } else {
            printf("List of loaded caches with found percentage:\n");
            printf("------------------------------------------------------------\n");
            printf("| Found% | Code | Name | State | Owner | Latitude | Longitude | Kind | Size | Difficulty | Terrain | Status | Hidden Date | Founds | Not Founds | Favourites | Altitude |\n");
            printf("------------------------------------------------------------\n");
            for (int i = 0; i < numCachesLoaded; i++) {
                displayCacheWithFoundPercentage(cacheData[i]);
            }
            printf("------------------------------------------------------------\n");
        }
        } else if (strcmp(command, "SEARCH") == 0 || strcmp(command, "search") == 0 || strcmp(command, "6") == 0) {
            // Implementar lógica para o comando SEARCH
        } else if (strcmp(command, "EDIT") == 0 || strcmp(command, "edit") == 0 || strcmp(command, "7") == 0) {
            // Implementar lógica para o comando EDIT
        } else if (strcmp(command, "CENTER") == 0 || strcmp(command, "center") == 0 || strcmp(command, "8") == 0) {
            // Implementar lógica para o comando CENTER
        } else if (strcmp(command, "AGE") == 0 || strcmp(command, "age") == 0 || strcmp(command, "9") == 0) {
            // Implementar lógica para o comando AGE
        } else if (strcmp(command, "SORT") == 0 || strcmp(command, "sort") == 0 || strcmp(command, "10") == 0) {
            int sortCriteria;
            printf("Enter sorting criteria (1-Altitude, 2-State, 3-Hidden Date): ");
            scanf("%d", &sortCriteria);

            sortCaches(cacheData, numCachesLoaded, sortCriteria);
            // A cacheData está ordenada com base no critério escolhido

            // Podesse imprimir ou realizar outras operações com os dados ordenados
        } else if (strcmp(command, "STATEC") == 0 || strcmp(command, "statec") == 0 || strcmp(command, "11") == 0) {
            //showCacheCountByState(cacheData, numCachesLoaded);
        } else if (strcmp(command, "M81") == 0 || strcmp(command, "m81") == 0 || strcmp(command, "12") == 0) {
            
        } else if (strcmp(command, "SAVE") == 0 || strcmp(command, "save") == 0 || strcmp(command, "13") == 0) {
            saveCachesToFile(cacheData, numCachesLoaded);
        } else {
            printf("Command not recognized.\n");
        }
    }

    return 0;
}
