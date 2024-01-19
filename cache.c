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

int compareByAltitude(const void *a, const void *b){
    return (*(Cache *)b).altitude - (*(Cache *)a).altitude;
}

int compareByStateAndFounds(const void *a, const void *b){
    int result = strcmp((*(Cache *)a).state, (*(Cache *)b).state);

    if(result == 0){
        return (*(Cache *)b).founds - (*(Cache *)a).founds;
    }

    return result;
}

int compareByHiddenDate(const void *a, const void *b){
    return strcmp((*(Cache *)b).hidden_date, (*(Cache *)a).hidden_date);
}

void sortCaches(Cache *cacheData, int numCachesLoaded, int criteria){
    switch (criteria) {
        case 1:
            qsort(cacheData, numCachesLoaded, sizeof(Cache), compareByAltitude);
            break;
        case 2:
            qsort(cacheData, numCachesLoaded, sizeof(Cache), compareByStateAndFounds);
            break;
        case 3:
            qsort(cacheData, numCachesLoaded, sizeof(Cache), compareByHiddenDate);
            break;
        default:
            printf("Invalid sorting criteria.\n");
            break;
    }
}

/*void showCacheCountByState(Cache *cacheData, int numCachesLoaded){
    // Arrays para armazenar as contagens por distrito e estado
    int countByState[MAX_STATES][2] = {0};

    for (int i = 0; i < numCachesLoaded; i++) {
        int stateIndex = getStateIndex(cacheData[i].state);

        if (stateIndex != -1) {
            // Incrementa a contagem correspondente ao distrito e estado da cache
            countByState[stateIndex][cacheData[i].status]++; 
        }
    }

    // Imprime as contagens
    printf("State\tAvailable\tDisabled\n");
    for (int i = 0; i < MAX_STATES; i++) {
        printf("%s\t%d\t\t%d\n", stateNames[i], countByState[i][AVAILABLE], countByState[i][DISABLED]);
    }
}

int getStateIndex(char *state) {
    for (int i = 0; i < MAX_STATES; i++) {
        if (strcmp(state, stateNames[i]) == 0) {
            return i;
        }
    }
    return -1; // Retorna -1 se o estado não for encontrado
}*/

void calculateMatrix81(Cache *cacheData, int numCachesLoaded, int matrix81[9][9]) {
    for (int i = 0; i < numCachesLoaded; i++) {
        int terrainIndex = (int)cacheData[i].terrain - 1; // Indices de 0 a 4
        int difficultyIndex = (int)cacheData[i].difficulty - 1; // Indices de 0 a 4

        // Incrementa a contagem para a combinação de terreno/dificuldade
        matrix81[terrainIndex][difficultyIndex]++;
    }
}

// Função para imprimir a matriz 81
void printMatrix81(int matrix81[9][9]) {
    printf("Matrix 81:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d\t", matrix81[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se um ficheiro já existe
int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1; // Retorna verdadeiro se o ficheiro existe
    }
    return 0; // Retorna falso se o ficheiro não existe
}

// Função para salvar as caches em formato CSV
void saveCachesToFile(Cache *cacheData, int numCachesLoaded) {
    char filename[50];

    // Solicita ao utilizador o nome do ficheiro
    printf("Enter the filename for saving: ");
    scanf("%s", filename);

    // Verifica se o ficheiro já existe
    if (fileExists(filename)) {
        printf("File '%s' already exists. Save operation aborted.\n", filename);
        return;
    }

    // Abre o ficheiro para escrita
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Escreve as informações das caches no ficheiro CSV
    for (int i = 0; i < numCachesLoaded; i++) {
        fprintf(file, "%s,%s,%s,%s,%lf\n", cacheData[i].code, cacheData[i].owner, cacheData[i].status,
                cacheData[i].hidden_date, cacheData[i].altitude);
    }

    fclose(file);
    printf("Caches saved to '%s' successfully.\n", filename);
}
