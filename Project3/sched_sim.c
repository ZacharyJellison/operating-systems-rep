#include "sched_sim.h"
#include <stdlib.h>

void init_Info(Sim_Info *simInfo, int size){
    simInfo->CPU_Burst = (int *)malloc(sizeof(int) * size);
    simInfo->priority = (int *)malloc(sizeof(int) * size);
    simInfo->arrivalTime = (int *)malloc(sizeof(int) * size);
    simInfo->size = size;
    simInfo->time = 0;
}


//FCFS
void *FCFS(void *args){
    printf("HELLO1 \n");
}

//SJF
void *SJF(void *args){
    printf("HELLO2 \n");
}

//STCF
void *STCF(void *args){
    printf("HELLO3 \n");
}

//ROUND ROBIN
void *RoundRobin(void *args){
    printf("HELLO4 \n");
}

//PRIORITY
void *Priority(void *args){
    printf("HELLO5 \n");
}