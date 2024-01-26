#ifndef CACHE_H
#define CACHE_H

#define MAX_CACHES 2000
#define MAX_STATES 2

typedef enum {
    EARTHCACHE,
    LETTERBOX,
    MULTI,
    PUZZLE,
    TRADITIONAL,
    VIRTUAL,
    WEBCAM,
    UNKNOWN_KIND
} CacheKind;

typedef enum {
    MICRO,
    SMALL,
    REGULAR,
    LARGE,
    OTHER_SIZE,
    VIRTUAL_SIZE,
    NOT_CHOSEN_SIZE,
    UNKNOWN_SIZE
} CacheSize;

typedef enum {
    AVAILABLE,
    DISABLED,
    UNKNOWN_STATUS
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

//Load
int isDuplicate(Cache *cacheData, int numCachesLoaded, char *code);
void loadCachesFromFile(Cache *cacheData, int *numCachesLoaded, char *filemane);

//Clear
void clearCacheData(Cache *cacheData, int *numCachesLoaded);

//List
void displayCache(Cache cache);

//FoundP
float calculateFoundPercentage(Cache cache);
void displayCacheWithFoundPercentage(Cache cache);

//Search
void searchCache(Cache *cacheData, int numCachesLoaded, const char *searchCode);
void displaySearchCache(Cache cache);

//Center
void calculateCenterStatistics(Cache *cacheData, int numCachesLoaded);

//Age
void calculateCacheAge(Cache *cacheData, int numCachesLoaded);

//Edit
void editCache(Cache *cacheData, int numCachesLoaded);

//Sort
void sortCaches(Cache *cacheData, int numCachesLoaded, int criteria);
void printCaches(const Cache *cacheData, int numCaches);

//State
void showCacheCountByState(Cache *cacheData, int numCachesLoaded);

//Matrix 81
void calculateMatrix81(Cache *cacheData, int numCachesLoaded, int matrix81[9][9]);
void printMatrix81(int matrix81[9][9]);

extern void saveCachesToFile(Cache cacheData[], int numCachesLoaded);


extern const char *stateNames[];
const char* cacheSizeToString(CacheSize size);
const char* cacheStatusToString(CacheStatus status);

CacheKind stringToCacheKind(const char *kindStr);
CacheSize stringToCacheSize(const char *sizeStr);
CacheStatus stringToCacheStatus(const char *statusStr);

#endif /*CACHE_H*/