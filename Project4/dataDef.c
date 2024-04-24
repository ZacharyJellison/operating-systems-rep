#include "dataDef.h"

extern pthread_mutex_t mutex;
extern pthread_mutex_t currentIndexMut;

void initInfo(PASSED_INFO *passedInfo, int mem, int page, int processes){
    passedInfo->memorySize = mem;
    passedInfo->pageSize = page;
    passedInfo->totalProcesses = processes;
}

int inArray(int numToFind, int arr[16]){
    for(int i = 0; i < 16; i++){
        if(numToFind == arr[i]){
            return 1;
        }
    }
    return 0;
}


void *child(void *args){
    PASSED_INFO *passedInfo = (PASSED_INFO *)args;
    int threadMemory;
    int registerNum[10];
    int addressNum[10];
    int personalThreadNum;

    char ReadWrite[10][2];

    srand(passedInfo->randomSeed);              //Set seed for rand

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
        int flag = 1;

        while(flag == 1){
            fprintf(passedInfo->output, "P%d OPERATION: %s r%d 0x%08X\n", personalThreadNum, ReadWrite[i], registerNum[i], addressNum[i]);
            sleep((rand() % 10) / 1000);
        

            if((inArray(registerNum[i], passedInfo->clockArr) == 0) || (inArray(registerNum[i], passedInfo->clockArr) == 1 && (passedInfo->clockPage[passedInfo->currentIndex].processIn != personalThreadNum))){
                fprintf(passedInfo->output, "P%d: page %d not resident in memory\n", personalThreadNum, passedInfo->clockPage[i].pageNum);
                
        
                if (passedInfo->clockPage[passedInfo->currentIndex].reference == 0){
                    fprintf(passedInfo->output, "P%d: using free frame %d\n", personalThreadNum, passedInfo->clockPage[passedInfo->currentIndex].index);
                    passedInfo->clockPage[passedInfo->currentIndex].pageNum = registerNum[i];
                    passedInfo->clockArr[passedInfo->currentIndex] = passedInfo->clockPage[passedInfo->currentIndex].pageNum;

                    passedInfo->clockPage[passedInfo->currentIndex].reference = 1;

                    fprintf(passedInfo->output, "P%d: new translation from page %d to frame %d\n", personalThreadNum, passedInfo->clockPage[passedInfo->currentIndex].pageNum, passedInfo->clockPage[passedInfo->currentIndex].index);
                    fprintf(passedInfo->output, "P%d: translated VA 0x%08X to PA 0x%08X\n", personalThreadNum, registerNum[i], addressNum[i]);              //Needs Fixing?
                    fprintf(passedInfo->output, "P%d: r%d = 0x%08X (mem at virtual addr 0x%08X)\n", personalThreadNum, addressNum[i], rand(), addressNum[i]);       //Needs Fixing
                    pthread_mutex_lock(&currentIndexMut);
                    passedInfo->currentIndex +=1;

                    if(passedInfo->currentIndex >= 16){
                        passedInfo->currentIndex = 0;
                    }

                    pthread_mutex_unlock(&currentIndexMut);
                }
                else if (passedInfo->clockPage[passedInfo->currentIndex].reference == 1){
                    pthread_mutex_lock(&currentIndexMut);
                    passedInfo->currentIndex +=1;

                    if(passedInfo->currentIndex >= 16){
                        passedInfo->currentIndex = 0;
                    }

                    pthread_mutex_unlock(&currentIndexMut);
                }
        
            }
            else if(inArray(registerNum[i], passedInfo->clockArr) == 1 && passedInfo->clockPage[passedInfo->currentIndex].processIn == personalThreadNum){
                passedInfo->clockPage[passedInfo->currentIndex].reference = 1;
            }

            flag = 0;
        }
    }

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




        fprintf(passedInfo->output, "Process %d complete\n", personalThreadNum);
        pthread_exit(NULL);
}
