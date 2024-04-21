#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>


typedef struct SUBSYSTEM{


}SUBSYSTEM;

typedef struct PASSED_INFO{
    int memorySize;
    int pageSize;
    int totalProcesses;

    char threadName[3][13];
}PASSED_INFO;

void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes);

//Child process that simulates different processes
void *childOne(void *args);
void *childTwo(void *args);
void *childThree(void *args);