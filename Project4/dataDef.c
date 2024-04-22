#include "dataDef.h"

void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes){
    passedInfo->memorySize = mem;
    passedInfo->pageSize = page;
    passedInfo->totalProcesses = processes;
}


void *childOne(void *args){
    PASSED_INFO *passedInfo = (PASSED_INFO *)args;
    int threadMemoryOne;
    int registerNumOne[10];
    int addressNumOne[10];


    char ReadWriteOne[10][2];

    FILE *fp;
    fp = fopen("thread1.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryOne);
    fprintf(passedInfo->output, "%d\n", threadMemoryOne);

//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWriteOne[i], &registerNumOne[i], &addressNumOne[i]);
    }

    fclose(fp);

    for(int i = 0; i < 10; i++){
        fprintf(passedInfo->output, "Read/Write:  %s", ReadWriteOne[i]);
        fprintf(passedInfo->output, "  Register:  %d", registerNumOne[i]);
        fprintf(passedInfo->output, "  Address:  %d\n", addressNumOne[i]);
    }

}


void *childTwo(void *args){
    PASSED_INFO *passedInfo = (PASSED_INFO *)args;
    int threadMemoryTwo;
    int registerNumTwo[10];
    int addressNumTwo[10];


    char ReadWriteTwo[10][2];

    FILE *fp;
    fp = fopen("thread2.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryTwo);
    fprintf(passedInfo->output, "%d\n", threadMemoryTwo);

//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWriteTwo[i], &registerNumTwo[i], &addressNumTwo[i]);
    }

    fclose(fp);

    for(int i = 0; i < 10; i++){
        fprintf(passedInfo->output, "Read/Write:  %s", ReadWriteTwo[i]);
        fprintf(passedInfo->output, "  Register:  %d", registerNumTwo[i]);
        fprintf(passedInfo->output, "  Address:  %d\n", addressNumTwo[i]);
    }

}


void *childThree(void *args){
    PASSED_INFO *passedInfo = (PASSED_INFO *)args;
    int threadMemoryThree;
    int registerNumThree[10];
    int addressNumThree[10];


    char ReadWriteThree[10][2];

    FILE *fp;
    fp = fopen("thread3.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryThree);
    fprintf(passedInfo->output, "%d\n", threadMemoryThree);

//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWriteThree[i], &registerNumThree[i], &addressNumThree[i]);
    }

    fclose(fp);

    for(int i = 0; i < 10; i++){
        fprintf(passedInfo->output, "Read/Write:  %s", ReadWriteThree[i]);
        fprintf(passedInfo->output, "  Register:  %d", registerNumThree[i]);
        fprintf(passedInfo->output, "  Address:  %d\n", addressNumThree[i]);
    }

}