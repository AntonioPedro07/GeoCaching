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

void loadCachesFromFile(Cache *cacheData, int *numCachesLoaded, char *fileman){
    FILE *file = fopen(fileman, "r");
    setlocale(LC_ALL, "pt-BR");
    if(file == NULL){
        printf("ERROR!! Ficheiro nao encontrado\n");
        return;
    }

    char tempCode[20];
    while(fscanf(file, "%s %s %s %s %lf", tempCode, cacheData[*numCachesLoaded].owner, 
        cacheData[*numCachesLoaded].status, cacheData[*numCachesLoaded].hidden_date, 
        &cacheData[*numCachesLoaded].altitude) != EOF){
            if(!isDuplicate(cacheData, *numCachesLoaded, tempCode)){
                strcpy(cacheData[*numCachesLoaded].code, tempCode);
                (*numCachesLoaded++);

                if(*numCachesLoaded >= MAX_CACHES){
                    printf("Limite maxima de capacidade alcacanda.\n");
                    break;
                }
            }
    }

    fclose(file);
    printf("<%d cache unica carregada>\n", numCachesLoaded);
}

void clearCacheData(Cache *cacheData, int *numCachesLoaded){
    *numCachesLoaded = 0;
    printf("Data cache limpa.\n");
}