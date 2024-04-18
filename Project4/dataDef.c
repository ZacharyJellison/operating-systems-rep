#include "dataDef.h"




void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes){
    passedInfo->memorySize = mem;
    passedInfo->pageSize = page;
    passedInfo->totalProcesses = processes;

//fix
    passedInfo->threadNames[3][13];

}


void *childOne(void *args){
    int threadMemoryOne;
    int registerNum[10];
    int addressNum[10];


    char ReadWrite[1][10];

    FILE *fp;
    fp = fopen("thread1.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryOne);
    printf("%d\n", threadMemoryOne);



//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWrite[i], &registerNum[i], &addressNum[i]);
        printf("%s\n", ReadWrite[i]);
    }

    fclose(fp);

}


void *childTwo(void *args){


}


void *childThree(void *args){


}