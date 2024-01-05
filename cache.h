#ifndef CACHE_H
#define CACHE_H

#define MAX_CACHES 2000

typedef enum {
    EARTHCACHE,
    LETTERBOX,
    MULTI,
    PUZZLE,
    TRADITIONAL,
    VIRTUAL,
    WEBCAM
} CacheKind;

typedef enum {
    MICRO,
    SMALL,
    REGULAR,
    LARGE,
    OTHER_SIZE,
    VIRTUAL_SIZE,
    NOT_CHOSEN_SIZE
} CacheSize;

typedef enum {
    AVAILABLE,
    DISABLED
} CacheStatus;

typedef struct {
    char code[20];
    char name[100]; 
    char state[50];
    char owner[50];
    double latitude;
    double longitude;
    CacheKind kind;
    CacheSize size;
    int difficulty;
    int terrain;
    CacheStatus status;
    char hidden_date[11]; 
    int founds;
    int not_founds;
    int favourites;
    double altitude;
} Cache;

int isDuplicate(Cache *cacheData, int numCachesLoaded, char *code);
void loadCachesFromFile(Cache *cacheData, int *numCachesLoaded, char *fileman);
void clearCacheData(Cache *cacheData, int *numCachesLoaded);

#endif /*CACHE_H*/