#include "dataDef.h"




void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes){
    passedInfo->memorySize = mem;
    passedInfo->pageSize = page;
    passedInfo->totalProcesses = processes;

}




void *childOne(void *args){
    int threadMemoryOne;
    int registerNum[10];
    int addressNum[10];


    char ReadWrite[10][1];

    FILE *fp;
    fp = fopen("thread1.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryOne);
    printf("%d\n", threadMemoryOne);



//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWrite[i], &registerNum[i], &addressNum[i]);
        printf("Read/Write:  %s", ReadWrite[i]);
        printf("  Register:  %d", registerNum[i]);
        printf("  Address:  %d\n", addressNum[i]);
    }

    fclose(fp);

}


void *childTwo(void *args){
    int threadMemoryOne;
    int registerNum[10];
    int addressNum[10];


    char ReadWrite[10][1];

    FILE *fp;
    fp = fopen("thread2.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryOne);
    printf("%d\n", threadMemoryOne);



//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWrite[i], &registerNum[i], &addressNum[i]);
        printf("Read/Write:  %s", ReadWrite[i]);
        printf("  Register:  %d", registerNum[i]);
        printf("  Address:  %d\n", addressNum[i]);
    }

    fclose(fp);

}


void *childThree(void *args){
    int threadMemoryOne;
    int registerNum[10];
    int addressNum[10];


    char ReadWrite[10][1];

    FILE *fp;
    fp = fopen("thread3.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryOne);
    printf("%d\n", threadMemoryOne);



//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWrite[i], &registerNum[i], &addressNum[i]);
        printf("Read/Write:  %s", ReadWrite[i]);
        printf("  Register:  %d", registerNum[i]);
        printf("  Address:  %d\n", addressNum[i]);
    }

    fclose(fp);

}