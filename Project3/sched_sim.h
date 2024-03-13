#include <stdio.h>


typedef struct Sim_Info{
    int* CPU_Burst;
    int* priority;
    int* arrivalTime;
    int size;
}Sim_Info;

void init_Info(Sim_Info simInfo, int size);