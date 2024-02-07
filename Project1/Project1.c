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
    childs = atoi(argv[1]);

//Less than 25 Children
    if(childs > 25){
        printf("Input out of Range.\n");
        return 0;
    }

    printf("Parent pid is %d\n", parent);

//Create Children: https://stackoverflow.com/questions/15328285/how-to-fork-an-exact-number-of-children
    for(int i = 0; i < childs; ++i){
        if(fork() == 0){
    //Print Start
            if(getpid() != parent){
                int childNumStart = abs(parent - getpid());
                printf("Started child %d with pid %d\n", childNumStart, getpid());
            }

    //Start a Process
            execv("test1", argv);


    //Print Finish
            if(getpid() != parent){
                int childNumFinish = abs(parent - getpid());
                printf("Child %d (PID %d) finsished\n", childNumFinish, getpid());
            }

            exit(0);        //End Process
        }
    }

    int status;
    for(int k = 0; k < childs; ++k){
        wait(&status);
    }

    return 0;
}