//#include "sched_sim.c"

#include <stdio.h>
#include <stdlib.h>

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

 //   int interval = atoi(argv[3]);
    int size = current_line;
    int size_all = size * 3;

    //printf("size: %d, sizeall: %d \n", size, size_all);

    int *all_input;
    all_input = (int *)malloc(sizeof(int) * size_all);

    for(int loop = 0; loop < size_all; loop++){
        fscanf(fp, "%d", &all_input[loop]);
    }

    fclose(fp);

    for(int loop = 0; loop < size_all; loop++){
        printf("%d ", all_input[loop]);
    }
    printf("\n");

    /*

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

    */
}