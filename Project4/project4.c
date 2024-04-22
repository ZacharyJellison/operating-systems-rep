#include "dataDef.c"



//      ./project4 infile.txt outfile.txt randomNumSeed

sem_t mutex;

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

//Everything above correctly reads and puts value   ----------------------------------------------------------------------------

//Open file to be written in

    FILE *output = fopen(argv[2], "w");
    passedInfo.output = output;
    passedInfo.threadIndexer = 0;

    sem_init(&mutex, 0, 1);


    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, child, &passedInfo);
    pthread_create(&thread2, NULL, child, &passedInfo);
    pthread_create(&thread3, NULL, child, &passedInfo);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    sem_destroy(&mutex);
    fprintf(output, "Main: program completed");
    fclose(output);

    return 0;
}