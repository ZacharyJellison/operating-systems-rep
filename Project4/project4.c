//#include "dataDef.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

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

    int memorySize;
    int pageSize;
    int totalProcesses;

    char threadNames[3][13] = {"thread1.txt\0", "thread2.txt\0", "thread3.txt\0"};        //Max of three threads

    printf("%s\n", threadNames[0]);
    printf("%s\n", threadNames[1]);
    printf("%s\n", threadNames[2]);


    //FILE *fp;
    //fp = fopen(argv[1], "r");


    return 0;
}