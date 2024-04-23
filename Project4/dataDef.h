#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <semaphore.h>


typedef struct PASSED_INFO{
    int memorySize;
    int pageSize;
    int totalProcesses;

    int clockPage[16];
    int clockIndex[16];

    char threadName[3][13];
    int threadIndexer;
    FILE *output;
}PASSED_INFO;

/*
typedef struct BIT_INFO{
    int dirty;
    int valid;
    int reference;
}BIT_INFO;
*/

void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes);

//Child process that simulates different processes
void *childOne(void *args);
void *childTwo(void *args);
void *childThree(void *args);