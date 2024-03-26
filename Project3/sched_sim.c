#include "sched_sim.h"

void init_Info(Sim_Info *simInfo, int size){
    simInfo->CPU_Burst = (int *)malloc(sizeof(int) * size);
    simInfo->priority = (int *)malloc(sizeof(int) * size);
    simInfo->arrivalTime = (int *)malloc(sizeof(int) * size);
    simInfo->size = size;
    simInfo->time = 0;

    simInfo->AVGwaitTime = (float *)malloc(sizeof(int) * size);
    simInfo->AVGturnTime = (float *)malloc(sizeof(int) * size);
    simInfo->contextSwitch = (float *)malloc(sizeof(int) * size);
}

//      https://www.learnc.net/c-tutorial/c-write-text-file/


void bubble(float arr[], int n) {         //Take input size and the array for either wait or turn around
    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so we don't need to check them again
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


//FCFS
void *FCFS(void *args) {
    passed_Info *functionInfo = (passed_Info *)args;
    int current_time = 0;
    float waiting_time = 0;
    float turnaround_time = 0;
    
    fprintf(functionInfo->output, "***** FCFS Scheduling *****\n");

    int n = functionInfo->simData->size;
    int* tempBurst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempBurst[i] = functionInfo->simData->CPU_Burst[i];
    }
    int i = 0;
    
    // Print initial state
    fprintf(functionInfo->output, "t = %d\n", current_time);
    fprintf(functionInfo->output, "CPU: Running process %d (remaining CPU burst = %d)\n", functionInfo->processID, tempBurst[i]);
    fprintf(functionInfo->output, "Ready queue: ");
    for (int j = i + 1; j < n; j++) {
        fprintf(functionInfo->output, "%d", functionInfo->processID);
        if (j < n - 1)
            fprintf(functionInfo->output, "-");
    }
    fprintf(functionInfo->output, "\n\n");
    
    while (tempBurst[i] > 0) {
        waiting_time += current_time - functionInfo->simData->arrivalTime[i];
        turnaround_time += current_time + tempBurst[i] - functionInfo->simData->arrivalTime[i];

        current_time += functionInfo->simData->interval;
        tempBurst[i] -= functionInfo->simData->interval;
        
        // Print updates at intervals
        fprintf(functionInfo->output, "t = %d\n", current_time);
        fprintf(functionInfo->output, "CPU: Running process %d (remaining CPU burst = %d)\n", functionInfo->processID, tempBurst[i]);
        fprintf(functionInfo->output, "Ready queue: ");
        for (int j = i + 1; j < n; j++) {
            fprintf(functionInfo->output, "%d", functionInfo->processID);
            if (j < n - 1)
                fprintf(functionInfo->output, "-");
        }
        fprintf(functionInfo->output, "\n\n");

        // Check if current process is completed
        if (tempBurst[i] <= 0 && i < n - 1) {
            i++; // Move to the next process
            // Print context switch message
            fprintf(functionInfo->output, "t = %d\n", current_time);
            fprintf(functionInfo->output, "CPU: Context switch\n");
            fprintf(functionInfo->output, "Ready queue: ");
            for (int j = i + 1; j < n; j++) {
                fprintf(functionInfo->output, "%d", functionInfo->processID);
                if (j < n - 1)
                    fprintf(functionInfo->output, "-");
            }
            fprintf(functionInfo->output, "\n\n");
        }
    }

    // Calculate average waiting and turnaround time
    functionInfo->simData->AVGwaitTime[0] = waiting_time / n;
    functionInfo->simData->AVGturnTime[0] = turnaround_time / n;

    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "FCFS Summary (WT = wait time, TT = turnaround time):\n\n");
    free(tempBurst);
    pthread_exit(NULL);
}


//SJF
void *SJF(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    //fprintf(functionInfo->output, "This is SJF\n");
    fprintf(functionInfo->output, "***** SJF Schedueling *****\n\n");


    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "SJF Summary (WT = wait time, TT = turnaround time):\n\n");
    pthread_exit(NULL);
}

//STCF
void *STCF(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    //fprintf(functionInfo->output, "This is STCF\n");
    fprintf(functionInfo->output, "***** STCF Schedueling *****\n\n");


    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "STCF Summary (WT = wait time, TT = turnaround time):\n\n");
    pthread_exit(NULL);
}

//ROUND ROBIN
void *RoundRobin(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    //fprintf(functionInfo->output, "This is Round Robin\n");
    fprintf(functionInfo->output, "***** Round robin Schedueling *****\n\n");


    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "Round robin Summary (WT = wait time, TT = turnaround time):\n\n");
    pthread_exit(NULL);
}

//PRIORITY
void *Priority(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    //fprintf(functionInfo->output, "This is Priority\n");
    fprintf(functionInfo->output, "***** Priority Schedueling *****\n\n");


    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "Priority Summary (WT = wait time, TT = turnaround time):\n\n");
    pthread_exit(NULL);
}

void *Summary(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    fprintf(functionInfo->output, "***** Overall Summary *****\n\n");

/*
    float* orderedWait;
    orderedWait = (float *)malloc(sizeof(int) * functionInfo->simData->size);
    orderedWait = functionInfo->simData->AVGwaitTime;
    bubble(orderedWait, functionInfo->simData->size);

    float* orderedTurn;
    orderedTurn = (float *)malloc(sizeof(int) * functionInfo->simData->size);
    orderedTurn = functionInfo->simData->AVGturnTime;
    bubble(orderedTurn, functionInfo->simData->size);

    float* orderedConSwitch;
    orderedConSwitch = (float *)malloc(sizeof(int) * functionInfo->simData->size);
    orderedConSwitch = functionInfo->simData->contextSwitch;
    bubble(orderedConSwitch, functionInfo->simData->size);
*/

    fprintf(functionInfo->output, "Wait Time Comparison\n");
    fprintf(functionInfo->output, "1  %.2lf\n", functionInfo->simData->AVGwaitTime[0]);
    fprintf(functionInfo->output, "2  %.2lf\n", 0.1);
    fprintf(functionInfo->output, "3  %.2lf\n", 0.1);
    fprintf(functionInfo->output, "4  %.2lf\n", 0.1);
    fprintf(functionInfo->output, "5  %.2lf\n\n", 0.1);

    fprintf(functionInfo->output, "Turnaround Time Comparison\n");
    fprintf(functionInfo->output, "1  %.2lf\n", functionInfo->simData->AVGturnTime[0]);
    fprintf(functionInfo->output, "2  %.2lf\n", 0.1);
    fprintf(functionInfo->output, "3  %.2lf\n", 0.1);
    fprintf(functionInfo->output, "4  %.2lf\n", 0.1);
    fprintf(functionInfo->output, "5  %.2lf\n\n", 0.1);

    fprintf(functionInfo->output, "Context Switch Comparison\n");
    fprintf(functionInfo->output, "1  %.0lf\n", 0.1);
    fprintf(functionInfo->output, "2  %.0lf\n", 0.1);
    fprintf(functionInfo->output, "3  %.0lf\n", 0.1);
    fprintf(functionInfo->output, "4  %.0lf\n", 0.1);
    fprintf(functionInfo->output, "5  %.0lf", 0.1);
}