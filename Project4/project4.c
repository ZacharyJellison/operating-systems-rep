#include "dataDef.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

//      ./project4 infile.txt outfile.txt randomNumSeed

int main(int argc, char **argv){
/*
Input:
    Main memory size (in bytes) (512)

    Page size (in bytes) (32)

    Number of processes to be simulated (1 thread = 1 process) (2 or 3)

    Which threads are picked
        thread1.txt
        thread2.txt
        thread3.txt
*/

    PASSED_INFO passedInfo;
    int memorySize;
    int pageSize;
    int totalProcesses;
    int randSeed = atoi(argv[3]);

    char threadNames[3][13];            //Max of 3 threads


    FILE *fp;
    fp = fopen(argv[1], "r");

//Interger assisnment
    printf("%d\n", randSeed);

    fscanf(fp, "%d", &memorySize);
    printf("%d\n", memorySize);

    fscanf(fp, "%d", &pageSize);
    printf("%d\n", pageSize);

    fscanf(fp, "%d", &totalProcesses);
    printf("%d\n", totalProcesses);

//Thread name assignment
    for(int i = 0; i < totalProcesses; i++){
        fscanf(fp, "%s ", threadNames[i]);
        strcpy(passedInfo.threadName[i], threadNames[i]);
        printf("%s\n", threadNames[i]);
    }

    fclose(fp);

    initInfo(&passedInfo, memorySize, pageSize, totalProcesses);

//Everything above correctly reads and puts value   ----------------------------------------------------------------------------

//Open file to be written in

    FILE *output = fopen(argv[2], "w");
    passedInfo.output = output;


    pthread_t thread_One;
    pthread_create(&thread_One, NULL, childOne, &passedInfo);


    pthread_t thread_Two;
    pthread_create(&thread_Two, NULL, childTwo, &passedInfo);


    pthread_t thread_Three;
    pthread_create(&thread_Three, NULL, childThree, &passedInfo);
    
    
    pthread_join(thread_One, NULL);
    pthread_join(thread_Two, NULL);
    pthread_join(thread_Three, NULL);


    fprintf(output, "Main: program completed");
    fclose(output);

    return 0;
}