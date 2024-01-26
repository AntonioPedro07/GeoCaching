#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "cache.h"

/*Código do LOAD*/

int isDuplicate(Cache *cacheData, int numCachesLoaded, char *code){
    for(int i = 0; i < numCachesLoaded; i++){
        if(strcmp(cacheData[i].code, code) == 0){
            return 1;
        }
    }
    return 0;
}

void trim(char *str) {
    int index, i;
    index = 0;

    // Trim leading white spaces
    while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n') {
        index++;
    }
    if (index != 0) {
        i = 0;
        while (str[i + index] != '\0') {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0';
    }

    // Trim trailing white spaces
    i = strlen(str) - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) {
        str[i] = '\0';
        i--;
    }
}

void loadCachesFromFile(Cache *cacheData, int *numCachesLoaded, char *fileman) {
      FILE *file = fopen(fileman, "r");
    if (file == NULL) {
        printf("ERROR!! Ficheiro nao encontrado\n");
        return;
    }

    char kindStr[20], sizeStr[20], statusStr[20];
    int continueReading = 1;
    char line[1024];
    int lineNum = 0;

    // Pular a linha do cabeçalho
    char header[1024];
    if (fgets(header, sizeof(header), file) == NULL) {
        printf("Erro ao ler o cabeçalho do arquivo.\n");
        fclose(file);
        return;
    }

   while (*numCachesLoaded < MAX_CACHES && continueReading && fgets(line, sizeof(line), file) != NULL) {
    lineNum++;
    trim(line); // Remove espaços extras e caracteres de nova linha

    printf("Linha %d: %s\n", lineNum, line);

    char *token = strtok(line, ";");
    int fieldCount = 0;

    while (token != NULL) {
        printf("Campo %d: %s\n", fieldCount + 1, token);
        switch (fieldCount) {
            case 0: strcpy(cacheData[*numCachesLoaded].code, token); break;
            case 1: strcpy(cacheData[*numCachesLoaded].name, token); break;
            case 2: strcpy(cacheData[*numCachesLoaded].state, token); break;
            case 3: strcpy(cacheData[*numCachesLoaded].owner, token); break;
            case 4: cacheData[*numCachesLoaded].latitude = atof(token); break;
            case 5: cacheData[*numCachesLoaded].longitude = atof(token); break;
            case 6: cacheData[*numCachesLoaded].kind = stringToCacheKind(token); break;
            case 7: cacheData[*numCachesLoaded].size = stringToCacheSize(token); break;
            case 8: cacheData[*numCachesLoaded].difficulty = atoi(token); break;
            case 9: cacheData[*numCachesLoaded].terrain = atoi(token); break;
            case 10: cacheData[*numCachesLoaded].status = stringToCacheStatus(token); break;
            case 11: strcpy(cacheData[*numCachesLoaded].hidden_date, token);break;
            case 12: cacheData[*numCachesLoaded].founds = atoi(token); break;
            case 13: cacheData[*numCachesLoaded].not_founds = atoi(token); break;
            case 14: cacheData[*numCachesLoaded].favourites = atoi(token); break;
            case 15: cacheData[*numCachesLoaded].altitude = atof(token); break;
        }
        token = strtok(NULL, ";");
        fieldCount++;
    }

    if (fieldCount != 16) {
        printf("Falha na leitura da linha %d. Número de campos esperado: 16, obtido: %d\n", lineNum, fieldCount);
        continueReading = 0; // Interrompe o loop
    } else {
        // Processamento normal
        printf("Loaded: %s\n", cacheData[*numCachesLoaded].code);
        (*numCachesLoaded)++;
    }
}
 
    if (*numCachesLoaded >= MAX_CACHES) {
        printf("Limite máximo de capacidade atingido.\n");  
    }

    fclose(file);
    printf("<%d cache unica carregada>\n", *numCachesLoaded);
}

CacheKind stringToCacheKind(const char *kindStr) {
    if (strcmp(kindStr, "EARTHCACHE") == 0) return EARTHCACHE;
    if (strcmp(kindStr, "LETTERBOX") == 0) return LETTERBOX;
    if (strcmp(kindStr, "MULTI") == 0) return MULTI;
    if (strcmp(kindStr, "PUZZLE") == 0) return PUZZLE;
    if (strcmp(kindStr, "TRADITIONAL") == 0) return TRADITIONAL;
    if (strcmp(kindStr, "VIRTUAL") == 0) return VIRTUAL;
    if (strcmp(kindStr, "WEBCAM") == 0) return WEBCAM;
    return UNKNOWN_KIND; // Um valor enum para representar um tipo desconhecido
}

CacheSize stringToCacheSize(const char *sizeStr){
    if (strcmp(sizeStr, "MICRO") == 0) return MICRO;
    if (strcmp(sizeStr, "SMALL") == 0) return SMALL;
    if (strcmp(sizeStr, "REGULAR") == 0) return REGULAR;
    if (strcmp(sizeStr, "LARGE") == 0) return LARGE;
    if (strcmp(sizeStr, "OTHER_SIZE") == 0) return OTHER_SIZE;
    if (strcmp(sizeStr, "VIRTUAL_SIZE") == 0) return VIRTUAL_SIZE;
    if (strcmp(sizeStr, "NOT_CHOSEN_SIZE") == 0) return NOT_CHOSEN_SIZE;
    return UNKNOWN_SIZE; // Um valor enum para representar um tipo desconhecido
}

CacheStatus stringToCacheStatus(const char *statusStr){
    if (strcmp(statusStr, "AVAILABLE") == 0) return AVAILABLE;
    if (strcmp(statusStr, "DISABLED") == 0) return DISABLED;
    return UNKNOWN_STATUS; // Um valor enum para representar um tipo desconhecido
}

/*Clear Data*/

void clearCacheData(Cache *cacheData, int *numCachesLoaded){
    *numCachesLoaded = 0;
    printf("Data cache limpa.\n");
}

/*Display List*/

const char* cacheKindToString(CacheKind kind) {
    switch (kind) {
        case EARTHCACHE: return "EARTHCACHE";
        case LETTERBOX: return "LETTERBOX";
        case MULTI: return "MULTI";
        case PUZZLE: return "PUZZLE";
        case TRADITIONAL: return "TRADITIONAL";
        case VIRTUAL: return "VIRTUAL";
        case WEBCAM: return "WEBCAM";
        // Adicione mais casos conforme necessário
        default: return "UNKNOWN";
    }
}

const char* cacheSizeToString(CacheSize size) {
    switch (size) {
        case MICRO:
            return "MICRO";
        case SMALL:
            return "SMALL";
        case REGULAR:
            return "REGULAR";
        case LARGE:
            return "LARGE";
        case OTHER_SIZE:
            return "OTHER_SIZE";
        case VIRTUAL_SIZE:
            return "VIRTUAL_SIZE";
        case NOT_CHOSEN_SIZE:
            return "NOT_CHOSEN_SIZE";
        // Adicione outros casos conforme necessário
        default:
            return "UNKNOWN_SIZE";
    }
}

const char* cacheStatusToString(CacheStatus status) {
    switch (status) {
        case AVAILABLE:
            return "AVAILABLE";
        case DISABLED:
            return "DISABLED";
        // Adicione outros casos conforme necessário
        default:
            return "UNKNOWN_STATUS";
    }
}

void displayCache(Cache cache) {
    printf("Code: %s | Name: %s | State: %s | Owner: %s | Latitude: %lf | Longitude: %lf | Kind: %s | Size: %s | Difficulty: %d | Terrain: %d | Status: %s | Hidden Date: %s | Founds: %d | Not Founds: %d | Favourites: %d | Altitude: %lf\n",
        cache.code, cache.name, cache.state, cache.owner, cache.latitude, cache.longitude,
        cacheKindToString(cache.kind), cacheSizeToString(cache.size), cache.difficulty,
        cache.terrain, cacheStatusToString(cache.status), cache.hidden_date, cache.founds,
        cache.not_founds, cache.favourites, cache.altitude);
}

/*Display List FoundP*/

float calculateFoundPercentage(Cache cache) {
    if (cache.founds + cache.not_founds == 0) {
        return 0.0;
    }
    return ((float)cache.founds / (cache.founds + cache.not_founds)) * 100.0;
}

void displayCacheWithFoundPercentage(Cache cache) {
    float foundPercentage = calculateFoundPercentage(cache);
    printf("%.2f%% | Code: %s | Name: %s | State: %s | Owner: %s | ... | Favourites: %d | Altitude: %lf\n",
        foundPercentage, cache.code, cache.name, cache.state, cache.owner, cache.favourites, cache.altitude);
}

/*Search*/

void displaySearchCache(Cache cache){
    printf("\nCache Details:\n");
    printf("Code: %s\n", cache.code);
    printf("Name: %s\n", cache.name);
    printf("State: %s\n", cache.state);
    printf("Owner: %s\n", cache.owner);
    printf("Latitude: %.2f\n", cache.latitude);
    printf("Longitude: %.2f\n", cache.longitude);
    printf("Kind: %s\n", cacheKindToString(cache.kind));
    printf("Size: %s\n", cacheSizeToString(cache.size));
    printf("Difficulty: %d\n", cache.difficulty);
    printf("Terrain: %d\n", cache.terrain);
    printf("Status: %s\n", cacheStatusToString(cache.status));
    printf("Hidden Date: %s\n", cache.hidden_date);
    printf("Founds: %d\n", cache.founds);
    printf("Not Founds: %d\n", cache.not_founds);
    printf("Favourites: %d\n", cache.favourites);
    printf("Altitude: %.2f\n", cache.altitude);
}

void searchCache(Cache *cacheData, int numCachesLoaded, const char *searchCode) {
    int found = 0;
 
    for (int i = 0; i < numCachesLoaded; i++) {
        if (strcmp(cacheData[i].code, searchCode) == 0) {
            // Cache encontrada, exibe informações
            displaySearchCache(cacheData[i]);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        // Cache não encontrada
        printf("<Cache not found>\n");
    }
}

/*Edit*/

void printCacheDetails(const Cache *cache) {
    printf("\nCache Details:\n");
    printf("Code: %s\n", cache->code);
    printf("Name: %s\n", cache->name);
    printf("State: %s\n", cache->state);
    printf("Owner: %s\n", cache->owner);
    printf("Latitude: %.2f\n", cache->latitude);
    printf("Longitude: %.2f\n", cache->longitude);
    printf("Kind: %s\n", cacheKindToString(cache->kind));
    printf("Size: %s\n", cacheSizeToString(cache->size));
    printf("Difficulty: %d\n", cache->difficulty);
    printf("Terrain: %d\n", cache->terrain);
    printf("Status: %s\n", cacheStatusToString(cache->status)); // Conversão de enum para string 
    printf("Hidden Date: %s\n", cache->hidden_date);
    printf("Founds: %d\n", cache->founds);
    printf("Not Founds: %d\n", cache->not_founds);
    printf("Favourites: %d\n", cache->favourites);
    printf("Altitude: %.2f\n", cache->altitude);
}

void editCache(Cache *cacheData, int numCachesLoaded) {
    char editCode[20];
    printf("\nEnter the cache code you want to edit: ");
    scanf("%s", editCode);
    
    int foundIndex = -1;
    int continueEditing = 1; // Inicia com 1 para entrar no loop pelo menos uma vez

    // Procura pela cache com base no código fornecido
    for (int i = 0; i < numCachesLoaded; i++) {
        if (strcmp(cacheData[i].code, editCode) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("<Cache not found>\n");
        return;
    }

   // Simula um processo de "loading"
     printf("Loading cache data...\n");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout); // Força a saída do buffer de printf
        Sleep(1000); // Espera 1000 milissegundos (1 segundo)
    }
    printf("\n");

    int choice;
    do {
        printf("\n\nEdit Cache - Choose an option:\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("1. Owner\n");
        printf("2. Status\n");
        printf("3. Hidden Date\n");
        printf("4. Altitude\n");
        printf("5. Exit\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consumir o caractere de nova linha pendente

        char input[50];
        switch (choice) {
            case 1: // Owner
                printf("\nEnter new owner: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) > 0) {
                    strcpy(cacheData[foundIndex].owner, input);
                }
                break;
            case 2: // Status
                printf("\nEnter new status: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) > 0) {
                    CacheStatus newStatus = stringToCacheStatus(input);
                    cacheData[foundIndex].status = newStatus;
                }
                break;
            case 3: // Hidden Date
                printf("\nEnter new hidden date (yyyy/mm/dd): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) > 0) {
                    strcpy(cacheData[foundIndex].hidden_date, input);
                }
                break;
            case 4: // Altitude
                printf("\nEnter new altitude: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) > 0) {
                    double newAltitude = atof(input);
                    cacheData[foundIndex].altitude = newAltitude;
                }
                break;
        }

        // Após a edição, imprime os detalhes da cache
        printCacheDetails(&cacheData[foundIndex]);

        printf("\nDo you want to edit more fields? (1 for Yes, 0 for No): ");
        scanf("%d", &continueEditing);
        getchar(); // Consumir o caractere de nova linha pendente
    } while (choice != 5 && continueEditing != 0);

    printf("<Cache information edited>\n");
}

/*Center*/

void calculateCenterStatistics(Cache *cacheData, int numCachesLoaded) {
    int validCaches = 0;
    double sumLatitudes = 0.0, sumLongitudes = 0.0;
    double sumLatitudesSquared = 0.0, sumLongitudesSquared = 0.0;
 
    for (int i = 0; i < numCachesLoaded; i++) {
        if (cacheData[i].altitude != -9999999) {
            // A cache tem uma altitude válida, inclui-a nos cálculos
            validCaches++;
            sumLatitudes += cacheData[i].latitude;
            sumLongitudes += cacheData[i].longitude;
            sumLatitudesSquared += pow(cacheData[i].latitude, 2);
            sumLongitudesSquared += pow(cacheData[i].longitude, 2);
        }
    }
 
    if (validCaches > 0) {
        // Calcula a média das latitudes e longitudes
        double meanLatitude = sumLatitudes / validCaches;
        double meanLongitude = sumLongitudes / validCaches;
 
        // Calcula o desvio padrão das latitudes e longitudes
        double stdDevLatitude = sqrt((sumLatitudesSquared / validCaches) - pow(meanLatitude, 2));
        double stdDevLongitude = sqrt((sumLongitudesSquared / validCaches) - pow(meanLongitude, 2));
 
        printf("\nCenter Statistics:\n");
        printf("Latitude: Mean= %.6lf, StdDev= %.6lf\n", meanLatitude, stdDevLatitude);
        printf("Longitude: Mean= %.6lf, StdDev= %.6lf\n", meanLongitude, stdDevLongitude);
    } else {
        printf("<No valid caches for center statistics>\n");
    }
}

/*Age*/

void calculateCacheAge(Cache *cacheData, int numCachesLoaded) {
    if (numCachesLoaded == 0) {
        printf("<No cache data>\n");
        return;
    }
 
    // Converte a data da primeira cache para a estrutura tm
    struct tm oldestDate;
    sscanf(cacheData[0].hidden_date, "%4d/%2d/%2d", &oldestDate.tm_year, &oldestDate.tm_mon, &oldestDate.tm_mday);
    oldestDate.tm_year -= 1900;  // tm_year conta a partir de 1900
    oldestDate.tm_mon -= 1;      // tm_mon é baseado em zero (0 = janeiro)
 
    // Converte a data da última cache para a estrutura tm
    struct tm newestDate;
    sscanf(cacheData[numCachesLoaded - 1].hidden_date, "%4d/%2d/%2d", &newestDate.tm_year, &newestDate.tm_mon, &newestDate.tm_mday);
    newestDate.tm_year -= 1900;  // tm_year conta a partir de 1900
    newestDate.tm_mon -= 1;      // tm_mon é baseado em zero (0 = janeiro)
 
    time_t oldestTime = mktime(&oldestDate);
    time_t newestTime = mktime(&newestDate);
 
    // Calcula a diferença em segundos entre as duas datas
    time_t timeDifference = difftime(newestTime, oldestTime);
 
    // Converte a diferença em meses
    int monthsDifference = (int)(timeDifference / (30 * 24 * 60 * 60));  // Aproximadamente 30 dias por mês
 
    printf("Oldest Cache: %s\n", cacheData[0].name);
    printf("Newest Cache: %s\n", cacheData[numCachesLoaded - 1].name);
    printf("Age Difference: %d months\n", monthsDifference);
}

/*Sort*/

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

void printCaches(const Cache *cacheData, int numCaches) {
    // Função para imprimir a lista de caches
    printf("Lista de Caches:\n");
    for (int i = 0; i < numCaches; i++) {
        printf("Cache %d:\n", i + 1);
        printf("Code: %s\n", cacheData[i].code);
        printf("Name: %s\n", cacheData[i].name);
        printf("State: %s\n", cacheData[i].state);
        printf("Owner: %s\n", cacheData[i].owner);
        printf("Latitude: %f\n", cacheData[i].latitude);
        printf("Longitude: %f\n", cacheData[i].longitude);
        // Aqui você pode imprimir mais informações conforme necessário
        printf("Altitude: %f\n", cacheData[i].altitude);
        printf("Hidden Date: %s\n", cacheData[i].hidden_date);
        printf("Founds: %d\n", cacheData[i].founds);
        printf("Not Founds: %d\n", cacheData[i].not_founds);
        printf("Favourites: %d\n\n", cacheData[i].favourites);
    }
}

/*State*/

int getStateIndex(const char *state) {
    for (int i = 0; i < MAX_STATES; i++) {
        if (strcmp(state, stateNames[i]) == 0) {
            return i;
        }
    }
    return -1; // Retorna -1 se o estado não for encontrado
}

void showCacheCountByState(Cache *cacheData, int numCachesLoaded){
    // Arrays para armazenar as contagens por distrito e estado
    int countByState[MAX_STATES][2] = {0};

    for (int i = 0; i < numCachesLoaded; i++) {
        int stateIndex = getStateIndex(cacheData[i].state);
        printf("Cache %d: State Index = %d, Status = %d\n", i, stateIndex, cacheData[i].status);

        if (stateIndex >= 0 && stateIndex < MAX_STATES && cacheData[i].status >= 0 && cacheData[i].status <= DISABLED) {
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

/*Matrix 81*/

void calculateMatrix81(Cache *cacheData, int numCachesLoaded, int matrix81[9][9]) {
    // Inicializa a matriz com 0s
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            matrix81[i][j] = 0;
        }
    }

    for (int i = 0; i < numCachesLoaded; i++) {
        if (cacheData[i].terrain >= 1 && cacheData[i].terrain <= 9 &&
            cacheData[i].difficulty >= 1 && cacheData[i].difficulty <= 9) {
            int terrainIndex = (int)cacheData[i].terrain - 1;
            int difficultyIndex = (int)cacheData[i].difficulty - 1;

            // Incrementa a contagem para a combinação de terreno/dificuldade
            matrix81[terrainIndex][difficultyIndex]++;
        }
    }
}

void printMatrix81(int matrix81[9][9]) {
    printf("Matrix 81:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d\t", matrix81[i][j]);
        }
        printf("\n");
    }
}

/*Save*/

int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1; // Retorna verdadeiro se o ficheiro existe
    }
    return 0; // Retorna falso se o ficheiro não existe
}

void saveCachesToFile(Cache *cacheData, int numCachesLoaded) {
    char filename[50];
    printf("\nEnter the filename for saving: ");
    scanf("%s", filename);

    if (fileExists(filename)) {
        printf("File '%s' already exists. Save operation aborted.\n", filename);
        return;
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    printf("Saving %d caches to file '%s'.\n", numCachesLoaded, filename);

    for (int i = 0; i < numCachesLoaded; i++) {
        printf("Writing cache %d: %s\n", i, cacheData[i].code);
        if (fprintf(file, "%s,%s,%s,%s,%s,%s,%.2lf,%.2lf,%d,%s,%d,%d,%d,%.2lf\n", 
                    cacheData[i].code, 
                    cacheData[i].owner,
                    cacheData[i].latitude,
                    cacheData[i].longitude,
                    cacheData[i].kind,
                    cacheData[i].size,
                    cacheData[i].difficulty,
                    cacheData[i].terrain,
                    cacheData[i].status, 
                    cacheData[i].hidden_date,
                    cacheData[i].founds,
                    cacheData[i].not_founds,
                    cacheData[i].favourites,
                    cacheData[i].altitude) < 0) {
            perror("Error writing to file");
            break;
        }
        printf("Cache %d written successfully: %s\n", i, cacheData[i].code);
    }

    if (fclose(file) != 0) {
        perror("Error closing file");
    } else {
        printf("File closed successfully.\n");
    }

    printf("Caches saved to '%s' successfully.\n", filename);
}