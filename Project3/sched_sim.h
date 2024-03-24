#include <stdio.h>

typedef struct Sim_Info{
    //Initial
    int size;
    int time;
    int* CPU_Burst;
    int* priority;
    int* arrivalTime;
    //Created After
    int* waitTime;
    int* turnaroundTime;
}Sim_Info;

void init_Info(Sim_Info *simInfo, int size);


//FCFS
void *FCFS(void *args);
//SJF
void *SJF(void *args);
//STCF
void *STCF(void *args);
//ROUND ROBIN
void *RoundRobin(void *args);
//PRIORITY
void *Priority(void *args);