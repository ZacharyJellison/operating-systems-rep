#include "sched_sim.h"

void init_Info(Sim_Info *simInfo, int size){
    simInfo->CPU_Burst = (int *)malloc(sizeof(int) * size);
    simInfo->priority = (int *)malloc(sizeof(int) * size);
    simInfo->arrivalTime = (int *)malloc(sizeof(int) * size);
    simInfo->size = size;
    simInfo->time = 0;

    simInfo->AVGwaitTime = (float *)malloc(sizeof(int) * size);
    simInfo->AVGturnTime = (float *)malloc(sizeof(int) * size);
    simInfo->contextSwitch = (int *)malloc(sizeof(int) * size);
}

//      https://www.learnc.net/c-tutorial/c-write-text-file/



//No reason to include priority
void bubbleInt(int burst[], int arrival[], int tasks[], int n) {         //Take input size and the array for either wait or turn around
    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so we don't need to check them again
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (burst[j] > burst[j + 1]) {
                int tempBurst = burst[j];
                int tempArrival = arrival[j];
                int tempTasks = tasks[j];
                burst[j] = burst[j + 1];
                arrival[j] = arrival[j+1];
                tasks[j] = tasks[j+1];
                burst[j + 1] = tempBurst;
                arrival[j + 1] = tempArrival;
                tasks[j + 1] = tempTasks;
            }
        }
    }
}

bool inArray(int val, int* arr, int n){
    for(int i = 0; i < n; i++) {
        if(arr[i] == val)
            return true;
    }
    return false;
}

int findIndex(int val, int* arr, int n){
    for(int i = 0; i < n; i++) {
        if(arr[i] == val)
            return i;
    }
    return 0;
}

//FCFS DONE
void *FCFS(void *args) {
    passed_Info *functionInfo = (passed_Info *)args;
    int current_time = 0;
    float waiting_time = 0;
    float turnaround_time = 0;
    int contextSwitches = 1;
    int* process_sequence = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* WT = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* TT = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* tasks = (int*)malloc(functionInfo->simData->size * sizeof(int));
    
    
    fprintf(functionInfo->output, "***** FCFS Scheduling *****\n");

    int n = functionInfo->simData->size;
    int* tempBurst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempBurst[i] = functionInfo->simData->CPU_Burst[i];
    }

    for(int q = 0; q < n; q++){
        tasks[q] = q;
    }

    int i = 0;
    
    // Print initial state
    fprintf(functionInfo->output, "t = %d\n", current_time);
    fprintf(functionInfo->output, "CPU: Loading process %d (remaining CPU burst = %d)\n", i, tempBurst[i]);
    fprintf(functionInfo->output, "Ready queue: ");
    for(int q = 0; q < n; q++){
        if(functionInfo->simData->arrivalTime[q] == 0)
            fprintf(functionInfo->output, "Ready queue: %d", tasks[q]);
    }

    fprintf(functionInfo->output, "\n\n");
    
    while (tempBurst[i] > 0) {
        WT[i] = current_time - functionInfo->simData->arrivalTime[i] - functionInfo->simData->CPU_Burst[i] + 1;
        TT[i] = current_time - functionInfo->simData->arrivalTime[i] + 1;

        current_time += 1;
        tempBurst[i] -= 1;
        
        // Print updates at intervals
        if(current_time % 10 == 0){
            fprintf(functionInfo->output, "t = %d\n", current_time);
            fprintf(functionInfo->output, "CPU: Running process %d (remaining CPU burst = %d)\n", i, tempBurst[i]);
            fprintf(functionInfo->output, "Ready queue: ");
//Ready Queue
            for(int q = 0; q < n; q++){
                if((functionInfo->simData->arrivalTime[q] <= current_time) && (i < q)){
                    fprintf(functionInfo->output, "%d", tasks[q]);
                    if((functionInfo->simData->arrivalTime[q+1] <= current_time) && (i < q+1) && (q < n-1)){
                        fprintf(functionInfo->output, "-");
                    }
                }
            }


            fprintf(functionInfo->output, "\n\n");
        }
        // Check if current process is completed
        if (tempBurst[i] <= 0 && i < n - 1) {
            i++; // Move to the next process
            contextSwitches++;
        }
    }

    // Calculate average waiting and turnaround time
    for(int k = 0; k < n; k++){
        waiting_time = waiting_time + WT[k];
    }
    functionInfo->simData->AVGwaitTime[0] = waiting_time / n;

    for(int k = 0; k < n; k++){
        turnaround_time = turnaround_time + TT[k];
    }
    functionInfo->simData->AVGturnTime[0] = turnaround_time / n;


// Print summary
    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "FCFS Summary (WT = wait time, TT = turnaround time):\n\n");
    fprintf(functionInfo->output, "PID\tWT\tTT\n");
    for (int j = 0; j < n; j++) {
        fprintf(functionInfo->output, " %d\t%d\t%d\n", j, WT[j], TT[j]);
    }
    fprintf(functionInfo->output, "AVG\t%.2f\t%.2f\n", functionInfo->simData->AVGwaitTime[0], functionInfo->simData->AVGturnTime[0]);
    fprintf(functionInfo->output, "\nProcess sequence: ");
    for (int j = 0; j < n; j++) {
        fprintf(functionInfo->output, "%d", j);
        if (j < n - 1)
            fprintf(functionInfo->output, "-");
    }
    fprintf(functionInfo->output, "\nContext switches: %d\n\n\n", contextSwitches);

    functionInfo->simData->contextSwitch[0] = contextSwitches;
    
    free(process_sequence);
    free(tempBurst);
    free(WT);
    free(TT);
    pthread_exit(NULL);
}


//SJF DONE
void *SJF(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    int current_time = 0;
    int contextSwitches = 1;
    int process[100];
    int* WT = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* TT = (int*)malloc(functionInfo->simData->size * sizeof(int));

    fprintf(functionInfo->output, "***** SJF Scheduling *****\n");

    int n = functionInfo->simData->size;
    int* tempBurst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempBurst[i] = functionInfo->simData->CPU_Burst[i];
    }

    int i = 0;
    int p = 0;
    process[0] = 0;
    int interval = functionInfo->simData->interval; // Interval for periodic updates

    // Print initial state
    fprintf(functionInfo->output, "t = %d\n", current_time);
    fprintf(functionInfo->output, "CPU: Loading process %d (remaining CPU burst = %d)\n", i, tempBurst[i]);
    fprintf(functionInfo->output, "Ready queue: %d", i);
    fprintf(functionInfo->output, "\n\n");

    int last_job = 0;
    int shortest_job = 0;

    while (1) {
        int shortest_burst = INT_MAX;

        // Find the shortest job in the ready queue once current job is finished
        if(tempBurst[shortest_job] < 1){
            for (int j = 0; j < n; j++) {
                if (tempBurst[j] > 0 && functionInfo->simData->arrivalTime[j] <= current_time && tempBurst[j] < shortest_burst) {
                    shortest_job = j;
                    shortest_burst = tempBurst[j];
                }
            }
            i++;
        }

        if(i > n-1)
            break;


            if(last_job != shortest_job){
                contextSwitches++;
                process[p+1] = shortest_job;
                p += 1;
            }

            last_job = shortest_job;

            if(shortest_job == -1)
                break;

        // Update time and execute the shortest job
        current_time += 1;
        tempBurst[shortest_job] -= 1;

        // Update waiting and turnaround time for the completed job
        WT[shortest_job] = current_time - functionInfo->simData->arrivalTime[shortest_job] - functionInfo->simData->CPU_Burst[shortest_job];
        TT[shortest_job] = current_time - functionInfo->simData->arrivalTime[shortest_job];

        // Check if it's time for a periodic update
        if (current_time % interval == 0) {
            // Print periodic update
            fprintf(functionInfo->output, "t = %d\n", current_time);
            fprintf(functionInfo->output, "CPU: Running process %d (remaining CPU burst = %d)", shortest_job, tempBurst[shortest_job]);
            fprintf(functionInfo->output, "\n");
            fprintf(functionInfo->output, "Ready queue: ");
            int count = 0;
            for (int q = 0; q < n; q++) {
                if (tempBurst[q] > 0 && functionInfo->simData->arrivalTime[q] <= current_time && (q != shortest_job)) {
                    fprintf(functionInfo->output, "%d ", q);
                    count ++;
                }
            }
            if(count == 0){
                fprintf(functionInfo->output, "empty");
            }
            fprintf(functionInfo->output, "\n\n");
        }
    }

    int* process_sequence = (int*)malloc(contextSwitches * sizeof(int));
    for(int y = 0; y < contextSwitches; y++){
        process_sequence[y] = process[y];
    }

    // Calculate average waiting and turnaround time
    float waiting_time = 0;
    float turnaround_time = 0;
    for (int k = 0; k < n; k++) {
        waiting_time += WT[k];
    }
    functionInfo->simData->AVGwaitTime[1] = waiting_time / n;

    for (int k = 0; k < n; k++) {
        turnaround_time += TT[k];
    }
    functionInfo->simData->AVGturnTime[1] = turnaround_time / n;


    // Print summary
    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "SJF Summary (WT = wait time, TT = turnaround time):\n\n");
    fprintf(functionInfo->output, "PID\tWT\tTT\n");
    for (int j = 0; j < n; j++) {
        fprintf(functionInfo->output, " %d\t%d\t%d\n", j, WT[j], TT[j]);
    }
    fprintf(functionInfo->output, "AVG\t%.2f\t%.2f\n", functionInfo->simData->AVGwaitTime[1], functionInfo->simData->AVGturnTime[1]);
    fprintf(functionInfo->output, "\nProcess sequence: ");
    for (int j = 0; j < contextSwitches; j++) {
        fprintf(functionInfo->output, "%d", process_sequence[j]);
        if (j < contextSwitches - 1)
            fprintf(functionInfo->output, "-");
    }
    fprintf(functionInfo->output, "\nContext switches: %d\n\n\n", contextSwitches);

    functionInfo->simData->contextSwitch[1] = contextSwitches;

    free(process_sequence);
    free(tempBurst);
    free(WT);
    free(TT);
    pthread_exit(NULL);
}


//STCF DONE
void *STCF(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    int current_time = 0;
    int contextSwitches = 0;
    int process[100];
    int* WT = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* TT = (int*)malloc(functionInfo->simData->size * sizeof(int));

    fprintf(functionInfo->output, "***** STCF Scheduling *****\n");

    int n = functionInfo->simData->size;
    int* tempBurst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempBurst[i] = functionInfo->simData->CPU_Burst[i];
    }

    int i = 0;
    int p = 0;
    process[0] = 0;
    int interval = functionInfo->simData->interval; // Interval for periodic updates

    // Print initial state
    fprintf(functionInfo->output, "t = %d\n", current_time);
    fprintf(functionInfo->output, "CPU: Loading process %d (remaining CPU burst = %d)\n", i, tempBurst[i]);
    fprintf(functionInfo->output, "Ready queue: %d", i);
    fprintf(functionInfo->output, "\n\n");

    int last_job = 0;

    while (1) {
        int shortest_job = -1;
        int shortest_burst = INT_MAX;

        // Find the shortest job in the ready queue

            for (int j = 0; j < n; j++) {
                if (tempBurst[j] > 0 && functionInfo->simData->arrivalTime[j] <= current_time && tempBurst[j] < shortest_burst) {
                    shortest_job = j;
                    shortest_burst = tempBurst[j];
                }
                
            }

            if(last_job != shortest_job){
                contextSwitches++;
                process[p+1] = shortest_job;
                p += 1;
            }

            last_job = shortest_job;

            if(shortest_job == -1)
                break;

        // Update time and execute the shortest job
        current_time += 1;
        tempBurst[shortest_job] -= 1;

        // Update waiting and turnaround time for the completed job
        WT[shortest_job] = current_time - functionInfo->simData->arrivalTime[shortest_job] - functionInfo->simData->CPU_Burst[shortest_job];
        TT[shortest_job] = current_time - functionInfo->simData->arrivalTime[shortest_job];

        if (i >= n)
            break;

        // Check if it's time for a periodic update
        if (current_time % interval == 0) {
            // Print periodic update
            fprintf(functionInfo->output, "t = %d\n", current_time);
            fprintf(functionInfo->output, "CPU: Running process %d (remaining CPU burst = %d)", shortest_job, tempBurst[shortest_job]);
            fprintf(functionInfo->output, "\n");
            fprintf(functionInfo->output, "Ready queue: ");
            int count = 0;
            for (int q = 0; q < n; q++) {
                if (tempBurst[q] > 0 && functionInfo->simData->arrivalTime[q] <= current_time && (q != shortest_job)) {
                    fprintf(functionInfo->output, "%d ", q);
                    count ++;
                }
            }
            if(count == 0){
                fprintf(functionInfo->output, "empty");
            }
            fprintf(functionInfo->output, "\n\n");
        }
    }

    int* process_sequence = (int*)malloc(contextSwitches * sizeof(int));
    for(int y = 0; y < contextSwitches; y++){
        process_sequence[y] = process[y];
    }

    // Calculate average waiting and turnaround time
    float waiting_time = 0;
    float turnaround_time = 0;
    for (int k = 0; k < n; k++) {
        waiting_time += WT[k];
    }
    functionInfo->simData->AVGwaitTime[2] = waiting_time / n;

    for (int k = 0; k < n; k++) {
        turnaround_time += TT[k];
    }
    functionInfo->simData->AVGturnTime[2] = turnaround_time / n;


    // Print summary
    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "STCF Summary (WT = wait time, TT = turnaround time):\n\n");
    fprintf(functionInfo->output, "PID\tWT\tTT\n");
    for (int j = 0; j < n; j++) {
        fprintf(functionInfo->output, " %d\t%d\t%d\n", j, WT[j], TT[j]);
    }
    fprintf(functionInfo->output, "AVG\t%.2f\t%.2f\n", functionInfo->simData->AVGwaitTime[2], functionInfo->simData->AVGturnTime[2]);
    fprintf(functionInfo->output, "\nProcess sequence: ");
    for (int j = 0; j < contextSwitches; j++) {
        fprintf(functionInfo->output, "%d", process_sequence[j]);
        if (j < contextSwitches - 1)
            fprintf(functionInfo->output, "-");
    }
    fprintf(functionInfo->output, "\nContext switches: %d\n\n\n", contextSwitches);

    functionInfo->simData->contextSwitch[2] = contextSwitches;

    free(process_sequence);
    free(tempBurst);
    free(WT);
    free(TT);
    pthread_exit(NULL);
}


//ROUND ROBIN
void *RoundRobin(void *args) {
    passed_Info *functionInfo = (passed_Info *)args;
    int current_time = 0;
    int contextSwitches = 0;
    int n = functionInfo->simData->size;
    int quantum = 2;

    int* WT = (int*)malloc(n * sizeof(int));
    int* TT = (int*)malloc(n * sizeof(int));
    int* tempBurst = (int*)malloc(n * sizeof(int));
    int* tempArrival = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        tempBurst[i] = functionInfo->simData->CPU_Burst[i];
        tempArrival[i] = functionInfo->simData->arrivalTime[i];
    }

    fprintf(functionInfo->output, "***** Round Robin Scheduling *****\n");

    // Print initial state
    fprintf(functionInfo->output, "t = %d\n", current_time);
    fprintf(functionInfo->output, "CPU: Loading process 0 (remaining CPU burst = %d)\n", tempBurst[0]);
    fprintf(functionInfo->output, "Ready queue: ");
    fprintf(functionInfo->output, "\n\n");

    // Main RR loop
while (true) {
    bool all_completed = true;

    for (int i = 0; i < n; i++) {
        for(int y = 0; y < quantum; y++){
        // Check if process has arrived and is not completed
        if (tempBurst[i] > 0 && tempArrival[i] <= current_time) {
            all_completed = false;

            // Execute the process for one time unit
            current_time += 1;
            tempBurst[i] -= 1;

            // Print periodic update
            if (current_time % functionInfo->simData->interval == 0) {
                fprintf(functionInfo->output, "t = %d\n", current_time);
                fprintf(functionInfo->output, "CPU: Running process %d (remaining CPU burst = %d)\n", i, tempBurst[i]);
                fprintf(functionInfo->output, "Ready queue: ");
                bool isQueueEmpty = true;

                for (int j = 0; j < n; j++) {
                    if (tempBurst[j] > 0 && tempArrival[j] <= current_time) {
                        fprintf(functionInfo->output, "%d ", j);
                        isQueueEmpty = false;
                    }
                }
                if (isQueueEmpty)
                    fprintf(functionInfo->output, "empty");
                fprintf(functionInfo->output, "\n\n");
            }

            // Check if process completed
            if (tempBurst[i] == 0) {
                // Process completed
                WT[i] = current_time - tempArrival[i] - functionInfo->simData->CPU_Burst[i];
                TT[i] = current_time - tempArrival[i];
            }
        }
        contextSwitches++;
        }
    }

    // Check if all processes are completed or if no more processes will arrive
    if (all_completed)
        break;

}


    // Calculate average waiting and turnaround time
    float total_wait_time = 0;
    float total_turnaround_time = 0;
    for (int k = 0; k < n; k++) {
        total_wait_time += WT[k];
        total_turnaround_time += TT[k];
    }
    functionInfo->simData->AVGwaitTime[3] = total_wait_time / n;
    functionInfo->simData->AVGturnTime[3] = total_turnaround_time / n;

    // Print summary
    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "Round Robin Summary (WT = wait time, TT = turnaround time):\n\n");
    fprintf(functionInfo->output, "PID\tWT\tTT\n");
    for (int j = 0; j < n; j++) {
        fprintf(functionInfo->output, " %d\t%d\t%d\n", j, WT[j], TT[j]);
    }
    fprintf(functionInfo->output, "AVG\t%.2f\t%.2f\n", functionInfo->simData->AVGwaitTime[3], functionInfo->simData->AVGturnTime[3]);
    fprintf(functionInfo->output, "\nContext switches: %d\n\n\n", contextSwitches / 4);

    // Update context switches count
    functionInfo->simData->contextSwitch[3] = contextSwitches / 4;

    // Free allocated memory
    free(tempBurst);
    free(WT);
    free(TT);

    pthread_exit(NULL);
}


//PRIORITY
void *Priority(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    int current_time = 0;
    float waiting_time = 0;
    float turnaround_time = 0;
    int contextSwitches = 0;
    int* process_sequence = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* WT = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* TT = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* tasks = (int*)malloc(functionInfo->simData->size * sizeof(int));
    
    
    
    fprintf(functionInfo->output, "***** Priority Scheduling *****\n");

    int n = functionInfo->simData->size;
    int* tempBurst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempBurst[i] = functionInfo->simData->CPU_Burst[i];
    }

    for(int q = 0; q < n; q++){
        tasks[q] = q;
    }

    int i = 0;
    int lowestPrio = 0;
    
    // Print initial state
    fprintf(functionInfo->output, "t = %d\n", current_time);
    fprintf(functionInfo->output, "CPU: Loading process %d (remaining CPU burst = %d)\n", i, tempBurst[i]);
    fprintf(functionInfo->output, "Ready queue: ");
    for(int q = 0; q < n; q++){
        if(functionInfo->simData->arrivalTime[q] == 0)
            fprintf(functionInfo->output, "Ready queue: %d", tasks[q]);
    }

    fprintf(functionInfo->output, "\n\n");

    //Create Priority
    int* priorityQ = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* burst = (int*)malloc(functionInfo->simData->size * sizeof(int));
    int* arrival = (int*)malloc(functionInfo->simData->size * sizeof(int));

    for (int i = 0; i < n; i++) {
        burst[i] = functionInfo->simData->CPU_Burst[i];
        priorityQ[i] = functionInfo->simData->priority[i];
        arrival[i] = functionInfo->simData->arrivalTime[i];
        tasks[i] = i;
    }

        if ((arrival[i] == 0) && (arrival[i] != arrival[i+1])){
            priorityQ[i] = 0;
        }

    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so we don't need to check them again
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (priorityQ[j] > priorityQ[j + 1]) {
                int tempBurst = burst[j];
                int tempArrival = arrival[j];
                int tempTasks = tasks[j];
                int tempQ = priorityQ[j];
                burst[j] = burst[j + 1];
                arrival[j] = arrival[j+1];
                tasks[j] = tasks[j+1];
                priorityQ[j] = priorityQ[j + 1];
                burst[j + 1] = tempBurst;
                arrival[j + 1] = tempArrival;
                tasks[j + 1] = tempTasks;
                priorityQ[j+1] = tempQ;
            }
        }
    }

    


    int nextProcess = 0;
    int currentProcess = 0;
    
    while (tempBurst[currentProcess] > 0) {
        WT[currentProcess] = current_time - functionInfo->simData->arrivalTime[currentProcess] - functionInfo->simData->CPU_Burst[currentProcess] + 2;
        TT[currentProcess] = current_time - functionInfo->simData->arrivalTime[currentProcess] + 2;

        current_time += 1;
        tempBurst[currentProcess] -= 1;
        
        // Print updates at intervals
        if(current_time % 10 == 0){
            fprintf(functionInfo->output, "t = %d\n", current_time);
            fprintf(functionInfo->output, "CPU: Running process %d (remaining CPU burst = %d)\n", currentProcess, tempBurst[i]);
            fprintf(functionInfo->output, "Ready queue: ");
//Ready Queue
            for(int q = 0; q < n; q++){
                if((arrival[q] <= current_time) && (inArray(q, process_sequence, n) == false)){
                    fprintf(functionInfo->output, "%d ", q);
                }
            }
            fprintf(functionInfo->output, "\n\n");
        }

        for(int l = 0; l < n; l++){
            if(((arrival[l] <= current_time) && (priorityQ[l] == lowestPrio)) || (currentProcess == nextProcess)){
                nextProcess = tasks[l];
            }
        }



        // Check if current process is completed
        if ((tempBurst[currentProcess] <= 1) && (i < n)) {
            int foundIndex = findIndex(currentProcess, tasks, n);
            process_sequence[i]= currentProcess;
            priorityQ[foundIndex] = 100;

        //find the index in tasks, use that for where to edit priority Q

            i++; // Move to the next process
            currentProcess = nextProcess;
            contextSwitches++;

            if(inArray(lowestPrio, priorityQ, n) == false){
                lowestPrio++;
            }
        }
    }

    // Calculate average waiting and turnaround time
    for(int k = 0; k < n; k++){
        waiting_time = waiting_time + WT[k];
    }
    functionInfo->simData->AVGwaitTime[4] = waiting_time / n;

    for(int k = 0; k < n; k++){
        turnaround_time = turnaround_time + TT[k];
    }
    functionInfo->simData->AVGturnTime[4] = turnaround_time / n;


// Print summary
    fprintf(functionInfo->output, "*********************************************************\n");
    fprintf(functionInfo->output, "Priority Summary (WT = wait time, TT = turnaround time):\n\n");
    fprintf(functionInfo->output, "PID\tWT\tTT\n");
    for (int j = 0; j < n; j++) {
        fprintf(functionInfo->output, " %d\t%d\t%d\n", j, WT[j], TT[j]);
    }
    fprintf(functionInfo->output, "AVG\t%.2f\t%.2f\n", functionInfo->simData->AVGwaitTime[4], functionInfo->simData->AVGturnTime[4]);
    fprintf(functionInfo->output, "\nProcess sequence: ");
    for (int j = 0; j < n; j++) {
        fprintf(functionInfo->output, "%d", process_sequence[j]);
        if (j < n - 1)
            fprintf(functionInfo->output, "-");
    }
    fprintf(functionInfo->output, "\nContext switches: %d\n\n\n", contextSwitches);

    functionInfo->simData->contextSwitch[4] = contextSwitches;
    
    free(process_sequence);
    free(tempBurst);
    free(WT);
    free(TT);
    pthread_exit(NULL);
}


void *Summary(void *args){
    passed_Info *functionInfo = (passed_Info *)args;
    int n = 5;
    fprintf(functionInfo->output, "***** Overall Summary *****\n\n");
    char sortingNames[5][20] = {"FCFS", "SJF", "STCF", "Round robin", "Priority"};
    //                            0       1       2          3             4


//Organize Wait
    int nameNumWait[5] = {0, 1, 2, 3, 4};

    float orderedWait[5];

    for(int u = 0; u < 5; u++){
        orderedWait[u] = functionInfo->simData->AVGwaitTime[u];
    }

    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so we don't need to check them again
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (orderedWait[j] > orderedWait[j + 1]) {
                int temp = orderedWait[j];
                int tempName = nameNumWait[j];
                orderedWait[j] = orderedWait[j + 1];
                nameNumWait[j] = nameNumWait[j + 1];
                orderedWait[j + 1] = temp;
                nameNumWait[j + 1] = tempName;
            }
        }
    }


//Organize Turn
    int nameNumTurn[5] = {0, 1, 2, 3, 4};

    float orderedTurn[5];

    for(int v = 0; v < 5; v++){
        orderedTurn[v] = functionInfo->simData->AVGturnTime[v];
    }

    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so we don't need to check them again
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (orderedTurn[j] > orderedTurn[j + 1]) {
                int temp2 = orderedTurn[j];
                int tempName2 = nameNumTurn[j];
                orderedTurn[j] = orderedTurn[j + 1];
                nameNumTurn[j] = nameNumTurn[j + 1];
                orderedTurn[j + 1] = temp2;
                nameNumTurn[j + 1] = tempName2;
            }
        }
    }


//Organize Context Switches
    int nameNumSwitch[5] = {0, 1, 2, 3, 4};

    int orderedSwitch[5];

    for(int u = 0; u < 5; u++){
        orderedSwitch[u] = functionInfo->simData->contextSwitch[u];
    }

    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so we don't need to check them again
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (orderedSwitch[j] > orderedSwitch[j + 1]) {
                int temp = orderedSwitch[j];
                int tempName = nameNumSwitch[j];
                orderedSwitch[j] = orderedSwitch[j + 1];
                nameNumSwitch[j] = nameNumSwitch[j + 1];
                orderedSwitch[j + 1] = temp;
                nameNumSwitch[j + 1] = tempName;
            }
        }
    }




    fprintf(functionInfo->output, "Wait Time Comparison\n");
    fprintf(functionInfo->output, "1 %s\t\t%.2lf\n", sortingNames[nameNumWait[0]], orderedWait[0]);
    fprintf(functionInfo->output, "2 %s\t\t%.2lf\n", sortingNames[nameNumWait[1]], orderedWait[1]);
    fprintf(functionInfo->output, "3 %s\t\t%.2lf\n", sortingNames[nameNumWait[2]], orderedWait[2]);
    fprintf(functionInfo->output, "4 %s\t\t%.2lf\n", sortingNames[nameNumWait[3]], orderedWait[3]);
    fprintf(functionInfo->output, "5 %s\t\t%.2lf\n\n", sortingNames[nameNumWait[4]], orderedWait[4]);

    fprintf(functionInfo->output, "Turnaround Time Comparison\n");
    fprintf(functionInfo->output, "1 %s\t\t%.2lf\n", sortingNames[nameNumTurn[0]], orderedTurn[0]);
    fprintf(functionInfo->output, "2 %s\t\t%.2lf\n", sortingNames[nameNumTurn[1]], orderedTurn[1]);
    fprintf(functionInfo->output, "3 %s\t\t%.2lf\n", sortingNames[nameNumTurn[2]], orderedTurn[2]);
    fprintf(functionInfo->output, "4 %s\t\t%.2lf\n", sortingNames[nameNumTurn[3]], orderedTurn[3]);
    fprintf(functionInfo->output, "5 %s\t\t%.2lf\n\n", sortingNames[nameNumTurn[4]], orderedTurn[4]);

    fprintf(functionInfo->output, "Context Switch Comparison\n");
    fprintf(functionInfo->output, "1 %s\t\t%d\n", sortingNames[nameNumSwitch[0]], orderedSwitch[0]);
    fprintf(functionInfo->output, "2 %s\t\t%d\n", sortingNames[nameNumSwitch[1]], orderedSwitch[1]);
    fprintf(functionInfo->output, "3 %s\t\t%d\n", sortingNames[nameNumSwitch[2]], orderedSwitch[2]);
    fprintf(functionInfo->output, "4 %s\t\t%d\n", sortingNames[nameNumSwitch[3]], orderedSwitch[3]);
    fprintf(functionInfo->output, "5 %s\t\t%d", sortingNames[nameNumSwitch[4]], orderedSwitch[4]);

}