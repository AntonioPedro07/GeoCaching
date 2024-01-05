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
        printf("Enter a command: ");
        scanf("%s", command);

        // Switch case para lidar com diferentes comandos
        if (strcmp(command, "LOAD") == 0) {
            printf("Enter file name: ");
            scanf("%s", filename);
            loadCachesFromFile(cacheData, &numCachesLoaded, filename);
        } else if (strcmp(command, "CLEAR") == 0) {
            clearCacheData(cacheData, &numCachesLoaded);
        } else if (strcmp(command, "QUIT") == 0) {
            running = 0;
        } else if (strcmp(command, "LIST") == 0) {
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
        } else if (strcmp(command, "FOUNDP") == 0) {
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
        } else if (strcmp(command, "SEARCH") == 0) {
            // Implementar lógica para o comando SEARCH
        } else if (strcmp(command, "EDIT") == 0) {
            // Implementar lógica para o comando EDIT
        } else if (strcmp(command, "CENTER") == 0) {
            // Implementar lógica para o comando CENTER
        } else if (strcmp(command, "AGE") == 0) {
            // Implementar lógica para o comando AGE
        } else if (strcmp(command, "SORT") == 0) {
            // Implementar lógica para o comando SORT
        } else if (strcmp(command, "STATEC") == 0) {
            // Implementar lógica para o comando STATEC
        } else if (strcmp(command, "M81") == 0) {
            // Implementar lógica para o comando M81
        } else if (strcmp(command, "SAVE") == 0) {
            // Implementar lógica para o comando SAVE
        } else {
            printf("Command not recognized.\n");
        }
    }

    return 0;
}
