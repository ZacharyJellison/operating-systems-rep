#include "sched_sim.h"

void init_Info(Sim_Info *simInfo, int size){
    simInfo->CPU_Burst = (int *)malloc(sizeof(int) * size);
    simInfo->priority = (int *)malloc(sizeof(int) * size);
    simInfo->arrivalTime = (int *)malloc(sizeof(int) * size);
    simInfo->size = size;
}