#include "dataDef.h"

extern sem_t mutex;

void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes){
    passedInfo->memorySize = mem;
    passedInfo->pageSize = page;
    passedInfo->totalProcesses = processes;
}


void *child(void *args){
    PASSED_INFO *passedInfo = (PASSED_INFO *)args;
    int threadMemory;
    int registerNum[10];
    int addressNum[10];
    int personalThreadNum;

    char ReadWrite[10][2];

    FILE *fp;

//Critical section to increment which thread get accessed and exit if total processes is reached
    sem_wait(&mutex);
        if (passedInfo->threadIndexer >= passedInfo->totalProcesses){
            pthread_exit(NULL);
        }
        fp = fopen(passedInfo->threadName[passedInfo->threadIndexer], "r");
        personalThreadNum = passedInfo->threadIndexer;
        passedInfo->threadIndexer += 1;
    sem_post(&mutex);

    fprintf(passedInfo->output, "Process %d started\n", personalThreadNum);

//Interger assisnment
    fscanf(fp, "%d", &threadMemory);
    //fprintf(passedInfo->output, "%d\n", threadMemory);

//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWrite[i], &registerNum[i], &addressNum[i]);
    }

    fclose(fp);

    for(int i = 0; i < 10; i++){
        fprintf(passedInfo->output, "P%d:  ", personalThreadNum);
        fprintf(passedInfo->output, "Read/Write:  %s", ReadWrite[i]);
        fprintf(passedInfo->output, "  Register:  %d", registerNum[i]);
        fprintf(passedInfo->output, "  Address:  %d\n", addressNum[i]);
    }


    fprintf(passedInfo->output, "Process %d complete\n", personalThreadNum);
    pthread_exit(NULL);
}

