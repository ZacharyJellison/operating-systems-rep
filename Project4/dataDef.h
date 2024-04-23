#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <semaphore.h>

typedef struct CLOCK_INFO{
    int index[16];
    int pageNum[16];

    //Bit Info
    int dirty[16];
    int valid[16];
    int reference[16];
}CLOCK_INFO;

typedef struct PASSED_INFO{
    int memorySize;
    int pageSize;
    int totalProcesses;
    int randomSeed;

    CLOCK_INFO clockPage[16];
    int currentIndex;

    char threadName[3][13];
    int threadIndexer;
    FILE *output;
}PASSED_INFO;


void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes);

//Child process that simulates different processes
void *childOne(void *args);
void *childTwo(void *args);
void *childThree(void *args);