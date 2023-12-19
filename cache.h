#ifndef CACHE_H
#define CACHE_H

#define MAX_CACHES 2000

typedef struct{
    char code[20];
    char owner[50];
    char status[20];
    char hidden_date[20];
    double altitude;
}Cache;

int isDuplicate(Cache *cacheData, int numCachesLoaded, char *code);
void loadCachesFromFile(Cache *cacheData, int *numCachesLoaded, char *fileman);
void clearCacheData(Cache *cacheData, int *numCachesLoaded);

#endif /*CACHE_H*/