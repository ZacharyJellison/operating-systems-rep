#include "dataDef.h"




void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes){
    passedInfo->memorySize = mem;
    passedInfo->pageSize = page;
    passedInfo->totalProcesses = processes;

}




void *childOne(void *args){
    int threadMemoryOne;
    int registerNumOne[10];
    int addressNumOne[10];


    char ReadWriteOne[10][1];

    FILE *fp;
    fp = fopen("thread1.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryOne);
    printf("%d\n", threadMemoryOne);



//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWriteOne[i], &registerNumOne[i], &addressNumOne[i]);
        printf("Read/Write:  %s", ReadWriteOne[i]);
        printf("  Register:  %d", registerNumOne[i]);
        printf("  Address:  %d\n", addressNumOne[i]);
    }

    fclose(fp);

}


void *childTwo(void *args){
    int threadMemoryTwo;
    int registerNumTwo[10];
    int addressNumTwo[10];


    char ReadWriteTwo[10][1];

    FILE *fp;
    fp = fopen("thread2.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryTwo);
    printf("%d\n", threadMemoryTwo);



//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWriteTwo[i], &registerNumTwo[i], &addressNumTwo[i]);
        printf("Read/Write:  %s", ReadWriteTwo[i]);
        printf("  Register:  %d", registerNumTwo[i]);
        printf("  Address:  %d\n", addressNumTwo[i]);
    }

    fclose(fp);

}


void *childThree(void *args){
    int threadMemoryThree;
    int registerNumThree[10];
    int addressNumThree[10];


    char ReadWriteThree[10][1];

    FILE *fp;
    fp = fopen("thread3.txt", "r");

//Interger assisnment
    fscanf(fp, "%d", &threadMemoryThree);
    printf("%d\n", threadMemoryThree);



//Thread name assignment
    for(int i = 0; i < 10; i++){
        fscanf(fp, "%s r%d %d", ReadWriteThree[i], &registerNumThree[i], &addressNumThree[i]);
        printf("Read/Write:  %s", ReadWriteThree[i]);
        printf("  Register:  %d", registerNumThree[i]);
        printf("  Address:  %d\n", addressNumThree[i]);
    }

    fclose(fp);

}