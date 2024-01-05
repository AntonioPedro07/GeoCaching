#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "cache.h"

int isDuplicate(Cache *cacheData, int numCachesLoaded, char *code){
    for(int i = 0; i < numCachesLoaded; i++){
        if(strcmp(cacheData[i].code, code) == 0){
            return 1;
        }
    }
    return 0;
}

void loadCachesFromFile(Cache *cacheData, int *numCachesLoaded, char *fileman) {
    FILE *file = fopen(fileman, "r");
    if (file == NULL) {
        printf("ERROR!! Ficheiro nao encontrado\n");
        return;
    }

    while (fscanf(file, "%s %s %s %s %lf %lf %d %d %d %d %d %s %d %d %d %lf", cacheData[*numCachesLoaded].code,
                  cacheData[*numCachesLoaded].name, cacheData[*numCachesLoaded].state, cacheData[*numCachesLoaded].owner,
                  &cacheData[*numCachesLoaded].latitude, &cacheData[*numCachesLoaded].longitude, 
                  (int *)&cacheData[*numCachesLoaded].kind, (int *)&cacheData[*numCachesLoaded].size,
                  &cacheData[*numCachesLoaded].difficulty, &cacheData[*numCachesLoaded].terrain,
                  (int *)&cacheData[*numCachesLoaded].status, cacheData[*numCachesLoaded].hidden_date,
                  &cacheData[*numCachesLoaded].founds, &cacheData[*numCachesLoaded].not_founds,
                  &cacheData[*numCachesLoaded].favourites, &cacheData[*numCachesLoaded].altitude) != EOF) {
        char tempCode[20];
        strcpy(tempCode, cacheData[*numCachesLoaded].code);

        if (!isDuplicate(cacheData, *numCachesLoaded, tempCode)) {
            (*numCachesLoaded)++;

            if (*numCachesLoaded >= MAX_CACHES) {
                printf("Limite maxima de capacidade alcacanda.\n");
                break;
            }
        }
    }

    fclose(file);
    printf("<%d cache unica carregada>\n", *numCachesLoaded);
}

void clearCacheData(Cache *cacheData, int *numCachesLoaded){
    *numCachesLoaded = 0;
    printf("Data cache limpa.\n");
}

void displayCache(Cache cache) {
    printf("Code: %s | Name: %s | State: %s | Owner: %s | Latitude: %lf | Longitude: %lf | Kind: %d | Size: %d | Difficulty: %d | Terrain: %d | Status: %d | Hidden Date: %s | Founds: %d | Not Founds: %d | Favourites: %d | Altitude: %lf\n",
        cache.code, cache.name, cache.state, cache.owner, cache.latitude, cache.longitude, cache.kind, cache.size, cache.difficulty, cache.terrain, cache.status, cache.hidden_date, cache.founds, cache.not_founds, cache.favourites, cache.altitude);
}

float calculateFoundPercentage(Cache cache) {
    if (cache.founds + cache.not_founds == 0) {
        return 0.0;
    }
    return ((float)cache.founds / (cache.founds + cache.not_founds)) * 100.0;
}

// Função para exibir as informações de uma única cache com a percentagem de encontrados
void displayCacheWithFoundPercentage(Cache cache) {
    float foundPercentage = calculateFoundPercentage(cache);
    printf("%.2f%% | Code: %s | Name: %s | State: %s | Owner: %s | ... | Favourites: %d | Altitude: %lf\n",
        foundPercentage, cache.code, cache.name, cache.state, cache.owner, cache.favourites, cache.altitude);
}
