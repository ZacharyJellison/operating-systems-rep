#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct CircularBuffer{
    int *buffer;
    int in;
    int out;
    int count;
    int size;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
}CircularBuffer;

typedef struct ThreadArgs{
    int producer_id;
    int consumer_id;
    CircularBuffer *buff;
} ThreadArgs;

void init_buffer(CircularBuffer *buff, int size);

void addVal(CircularBuffer *buff, int item);
int delVal(CircularBuffer *buff);

void *producer(void *args);
void *consumer(void *args);