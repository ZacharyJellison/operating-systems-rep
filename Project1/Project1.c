#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>


int main(int argc, char **argv){

//Setup
    pid_t pid;
    pid_t parent = getpid();
    int childs;
    childs = atoi("2");

    printf("Parent pid is %d\n", parent);

//Create Children
    for(int i = 0; i < childs; i++){
        fork();
    }

//Print Start
    if(getpid() != parent){
        int childNumStart = abs(parent - getpid());
        printf("Started child %d with pid %d\n", childNumStart, getpid());
    }



//Start a Process


//Print Finish
    if(getpid() != parent){
        int childNumFinish = abs(parent - getpid());
        printf("Child %d (PID %d) finsished\n", childNumFinish, getpid());
    }

    return 0;
}