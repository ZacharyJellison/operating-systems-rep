#include "sched_sim.c"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char **argv){     /*
Input 1 is program
Input 2 is input data             EX. testin1.dat
    Contains:
     CPU burst time
     Priority (lower number is higher priority)
     Arrival Time (arrive at T starts at T + 1)
Input 3 is output data            EX. out1.txt
Input 4 is interval between scheduler snapshots     */
    FILE *fp;
    fp = fopen(argv[1], "r");

//Find number of lines in file

    int current_line = 1;
    char c;

    do{
        c = fgetc(fp);
        if (c == '\n'){
            current_line++;
        }
    } while (c != EOF);

    int interval = atoi(argv[3]);
    int size = current_line;
    int size_all = size * 3;

    int *all_input;
    all_input = (int *)malloc(sizeof(int) * size_all);

    fseek(fp, 0, SEEK_SET);     //Return to start of file

    for(int loop = 0; loop < size_all; loop++){
        fscanf(fp, "%d ", &all_input[loop]);
    }

    fclose(fp);

// Create for loops to read simulation info
//First find number of processes to create sim info
//Create Info Strucutre
    Sim_Info simDat;
    init_Info(&simDat, size);

    int inputIndex = 0;
    for (int i = 0; i < size; i++){     //Read data and put to structure
        simDat.CPU_Burst[i] = all_input[inputIndex];
        inputIndex++;
        simDat.priority[i] = all_input[inputIndex];
        inputIndex++;
        simDat.arrivalTime[i] = all_input[inputIndex];
        inputIndex++;
    }
//ALL CODE ABOVE WORKS, SAVES ALL INPUT DATA TO A
//DATA STRUCTURE THAT VARIES IN SIZE DEPENDENT ON INPUT

//FCFS
    pthread_t fcfs_thread;
    pthread_create(&fcfs_thread, NULL, FCFS, &simDat);
    pthread_join(fcfs_thread, NULL);
//SJF
    pthread_t sjf_thread;
    pthread_create(&sjf_thread, NULL, SJF, &simDat);
    pthread_join(sjf_thread, NULL);
//STCF
    pthread_t stcf_thread;
    pthread_create(&stcf_thread, NULL, STCF, &simDat);
    pthread_join(stcf_thread, NULL);
//ROUND ROBIN
    pthread_t RR_thread;
    pthread_create(&RR_thread, NULL, RoundRobin, &simDat);
    pthread_join(RR_thread, NULL);
//PRIORITY
    pthread_t prio_thread;
    pthread_create(&prio_thread, NULL, Priority, &simDat);
    pthread_join(prio_thread, NULL);
}