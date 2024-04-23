#include "dataDef.h"

extern pthread_mutex_t mutex;

void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes){
    passedInfo->memorySize = mem;
    passedInfo->pageSize = page;
    passedInfo->totalProcesses = processes;
}


void *child(void *args){
    PASSED_INFO *passedInfo = (PASSED_INFO *)args;
    int threadMemory;
    int registerNum[10];
    unsigned int addressNum[10];
    int personalThreadNum;

    char ReadWrite[10][2];

    FILE *fp;


//Critical section to increment which thread get accessed and exit if total processes is reached
    pthread_mutex_lock(&mutex);
        fp = fopen(passedInfo->threadName[passedInfo->threadIndexer], "r");
        personalThreadNum = passedInfo->threadIndexer;
        passedInfo->threadIndexer += 1;
    pthread_mutex_unlock(&mutex);

    fprintf(passedInfo->output, "Process %d started\n", personalThreadNum);

//Interger assisnment
    fscanf(fp, "%d", &threadMemory);
    //fprintf(passedInfo->output, "%d\n", threadMemory);

//Thread name assignment
    for (int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWrite[i], &registerNum[i], &addressNum[i]);
    }

    fclose(fp);




//THIS IS IMPORTANT FOR LOOP IT RUN THROUGH ALL 10 PAGES NEED MUTEX FOR WHEN ACCESSING CLOCK MEMORY
    for (int i = 0; i < 10; i++){
        fprintf(passedInfo->output, "P%d OPERATION: %s r%d 0x%08X\n", personalThreadNum, ReadWrite[i], registerNum[i], addressNum[i]);
        sleep((rand() % 10) / 1000);





//All Output messages
/*
    int i = 0;
    fprintf(passedInfo->output, "P%d OPERATION: %s r%d 0x%08X\n", personalThreadNum, ReadWrite[i], registerNum[i], addressNum[i]);
    fprintf(passedInfo->output, "P%d: page %d not resident in memory\n", personalThreadNum, passedInfo->clockPage[i].pageNum[i]);
    fprintf(passedInfo->output, "P%d: using free frame %d\n", personalThreadNum, passedInfo->clockPage[i].index[i]);
    fprintf(passedInfo->output, "P%d: new translation from page %d to frame %d\n", personalThreadNum, passedInfo->clockPage[i].pageNum[i], passedInfo->clockPage[i].index[i]);
    fprintf(passedInfo->output, "P%d: translated VA 0x%08X to PA 0x%08X\n", personalThreadNum, registerNum[i], addressNum[i]);      //Needs Fixing
    fprintf(passedInfo->output, "P%d: r%d = 0x%08X (mem at virtual addr 0x%08X)\n", personalThreadNum, addressNum[i], addressNum[i]);       //Needs Fixing
    fprintf(passedInfo->output, "P%d: valid translation from page %d to frame %d\n", personalThreadNum, passedInfo->clockPage[i].pageNum[i], passedInfo->clockPage[i].index[i]);
    fprintf(passedInfo->output, "P%d: evicting process %d, page %d from frame %d\n", personalThreadNum, passedInfo->clockPage[i].processIn[i], passedInfo->clockPage[i].pageNum[i], passedInfo->clockPage[i].index[i]);
*/




    }





    fprintf(passedInfo->output, "Process %d complete\n", personalThreadNum);
    pthread_exit(NULL);
}

