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
    int index;
    int pageNum;        //Page number in the index
    int processIn;      //What process is int the clock index

    //Bit Info
    int dirty;
    int valid;
    int reference;
}CLOCK_INFO;

typedef struct PASSED_INFO{
    int memorySize;
    int pageSize;
    int totalProcesses;
    int randomSeed;
    int clockArr[16];

    CLOCK_INFO clockPage[16];
    int currentIndex;

    char threadName[3][13];
    int threadIndexer;
    FILE *output;
}PASSED_INFO;


void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes);

int inArray(int numToFind, int arr[16]);

int clockFull(CLOCK_INFO *input);

//Child process that simulates different processes
void *childOne(void *args);
void *childTwo(void *args);
void *childThree(void *args);