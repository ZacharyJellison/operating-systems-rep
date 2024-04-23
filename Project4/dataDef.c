#include "dataDef.h"

extern sem_t mutex;
extern sem_t outputMut;

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
    for (int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWrite[i], &registerNum[i], &addressNum[i]);
    }

    fclose(fp);

    for (int i = 0; i < 10; i++){
        sem_wait(&outputMut);
        fprintf(passedInfo->output, "P%d:  ", personalThreadNum);
        fprintf(passedInfo->output, "Read/Write:  %s", ReadWrite[i]);
        fprintf(passedInfo->output, "  Register:  %d", registerNum[i]);
        fprintf(passedInfo->output, "  Address:  %d\n", addressNum[i]);
        sem_post(&outputMut);
    }





//All Output messages
/*
    fprintf(passedInfo->output, "P%d OPERATION: %s r%d 0x%d", personalThreadNum, );
    fprintf(passedInfo->output, "P%d: page %d not resident in memory ", personalThreadNum, );
    fprintf(passedInfo->output, "P%d: using free frame %d", personalThreadNum, );
    fprintf(passedInfo->output, "P%d: new translation from page %d to frame %d", personalThreadNum, );
    fprintf(passedInfo->output, "P%d: translated VA 0x%d to PA 0x%d", personalThreadNum, );
    fprintf(passedInfo->output, "P%d: r%d = 0x%d (mem at virtual addr 0x%d)", personalThreadNum, );
    fprintf(passedInfo->output, "P%d: valid translation from page %d to frame %d", personalThreadNum, );
    fprintf(passedInfo->output, "P%d: evicting process %d, page %d from frame %d", personalThreadNum, );




*/




    fprintf(passedInfo->output, "Process %d complete\n", personalThreadNum);
    pthread_exit(NULL);
}

