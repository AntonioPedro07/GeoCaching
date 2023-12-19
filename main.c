#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "cache.h"

int main() {

    Cache cacheData[MAX_CACHES];
    int numCachesLoaded = 0;

    loadCachesFromFile(cacheData, &numCachesLoaded, "caches_all.csv");
    clearCacheData(cacheData, &numCachesLoaded);

    return 0;
}

