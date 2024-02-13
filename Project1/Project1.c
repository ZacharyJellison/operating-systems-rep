#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


void execute_test(char *test_program, int child_num) {
    char child_str[10];
    snprintf(child_str, sizeof(child_str), "%d", child_num);
    char *tests[] = {test_program, child_str, NULL};
    printf("Started child %d with pid %d\n", child_num, getpid());
    execv(tests[0], tests);
//Error Case ----- Should never happen
    perror("execv");
    exit(1);
}


int main(int argc, char **argv){
//Setup
    int children;

    pid_t parent = getpid();

    children = atoi(argv[1]);

//Less than 25 Children
    if(children > 25){
        printf("Input out of Range.\n");
        return 0;
    }

    printf("Parent pid is %d\n", parent);


// Loop to create child processes
    for (int i = 0; i < children; i++) {
        pid_t pid = fork();
        
        // Child Process Selection and Execution
        if (pid == 0) {
            switch(i % 5) {
                case 0:
                    execute_test("test1", i+1);
                    break;
                case 1:
                    execute_test("test2", i+1);
                    break;
                case 2:
                    execute_test("test3", i+1);
                    break;
                case 3:
                    execute_test("test4", i+1);
                    break;
                case 4:
                    execute_test("test5", i+1);
                    break;
                default:
                //Should Never Happen
                    printf("Invalid test program.\n");
                    exit(1);
            }
        }
    }


//Wait for Children
    for (int k = 0; k < children; ++k) {
        int status;
        pid_t finished_pid = wait(&status);
        printf("Child %d (pid: %d) finished\n", k + 1, finished_pid);
    }

    return 0;
}