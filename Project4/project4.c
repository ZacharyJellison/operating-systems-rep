#include "dataDef.c"



//      ./project4 infile.txt outfile.txt randomNumSeed

pthread_mutex_t mutex, currentIndexMut, printing;

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
    //printf("%d\n", randSeed);

    fscanf(fp, "%d", &memorySize);
    //printf("%d\n", memorySize);

    fscanf(fp, "%d", &pageSize);
    //printf("%d\n", pageSize);

    fscanf(fp, "%d", &totalProcesses);
    //printf("%d\n", totalProcesses);

//Thread name assignment
    for(int i = 0; i < totalProcesses; i++){
        fscanf(fp, "%s ", threadNames[i]);
        strcpy(passedInfo.threadName[i], threadNames[i]);
        //printf("%s\n", threadNames[i]);
    }

    fclose(fp);

    initInfo(&passedInfo, memorySize, pageSize, totalProcesses);

    for (int i = 0; i < 16; i++){
        passedInfo.clockPage[i].index = i;
        passedInfo.clockPage[i].reference = 0;
        passedInfo.clockPage[i].processIn = -1;     //No process inside until one is places in
    }

    passedInfo.currentIndex = 0;
    passedInfo.randomSeed = randSeed;
    passedInfo.currentIndex = 0;            //Start clock at 0, use mutex to edit


//Open file to be written in

    FILE *output = fopen(argv[2], "w");
    passedInfo.output = output;
    passedInfo.threadIndexer = 0;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&currentIndexMut, NULL);
    pthread_mutex_init(&printing, NULL);

//3 Threads max
    pthread_t thread[3];
    for (int t = 0; t < totalProcesses; t++){
        pthread_create(&thread[t], NULL, child, &passedInfo);
    }


    for (int t = 0; t < totalProcesses; t++){
        pthread_join(thread[t], NULL);
    }

    pthread_mutex_destroy(&printing);
    pthread_mutex_destroy(&currentIndexMut);
    pthread_mutex_destroy(&mutex);

    fprintf(output, "Main: program completed");
    fclose(output);

    return 0;
}