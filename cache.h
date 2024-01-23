#ifndef CACHE_H
#define CACHE_H

#define MAX_CACHES 2000
#define MAX_STATES 20

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
void loadCachesFromFile(Cache *cacheData, int *numCachesLoaded, char *filemane);
void clearCacheData(Cache *cacheData, int *numCachesLoaded);
void displayCache(Cache cache);
float calculateFoundPercentage(Cache cache);
void displayCacheWithFoundPercentage(Cache cache);
void sortCaches(Cache *cacheData, int numCachesLoaded, int criteria);
void showCacheCountByState(Cache *cacheData, int numCachesLoaded);
void calculateMatrix81(Cache *cacheData, int numCachesLoaded, int matrix81[9][9]);

extern void saveCachesToFile(Cache cacheData[], int numCachesLoaded);
extern const char *stateNames[];
const char* cacheSizeToString(CacheSize size);
const char* cacheStatusToString(CacheStatus status);


#endif /*CACHE_H*/