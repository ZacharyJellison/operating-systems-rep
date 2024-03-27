#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

typedef struct Sim_Info{
    //Initial
    int size;
    int time;
    int interval;
    int* CPU_Burst;
    int* priority;
    int* arrivalTime;
    //Created
    float* AVGwaitTime;
    float* AVGturnTime;
    int* contextSwitch;
}Sim_Info;

typedef struct passed_Info{
    int processID;
    Sim_Info *simData;
    FILE *output;
}passed_Info;

void init_Info(Sim_Info *simInfo, int size);

//Extra Functions
void bubble(float arr[], int n);

//FCFS          ASSOCIATED WITH 0
void *FCFS(void *args);
//SJF           ASSOCIATED WITH 1
void *SJF(void *args);
//STCF          ASSOCIATED WITH 2
void *STCF(void *args);
//ROUND ROBIN   ASSOCIATED WITH 3
void *RoundRobin(void *args);
//PRIORITY      ASSOCIATED WITH 4
void *Priority(void *args);

//Summary
void *Summary(void *args);