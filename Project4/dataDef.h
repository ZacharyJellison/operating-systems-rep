#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>


typedef struct SUBSYSTEM{



}SUBSYSTEM;


//Child process that simulates different processes
void *child(void *args);