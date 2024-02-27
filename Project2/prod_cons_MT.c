#include "prod_cons_MT.h"

//Global Variable for Producers
bool producers_finished = false;

void init_buffer(CircularBuffer *buff, int size) {
    buff->buffer = (int *)malloc(sizeof(int) * size);
    buff->in = 0;
    buff->out = 0;
    buff->count = 0;
    buff->size = size;
    pthread_mutex_init(&buff->lock, NULL);
    pthread_cond_init(&buff->not_full, NULL);
    pthread_cond_init(&buff->not_empty, NULL);
}

void addVal(CircularBuffer *buff, int item) {
    int wait = 0;
    pthread_mutex_lock(&buff->lock);
    while (buff->count == buff->size) {
        pthread_cond_wait(&buff->not_full, &buff->lock);
        printf("Blocked due to full buffer\n");
        wait = 1;
    }
    if(wait == 1){
        printf("Done waiting on full buffer\n");
        wait = 0;
    }
    buff->buffer[buff->in] = item;
    buff->in = (buff->in + 1) % buff->size;
    buff->count++;
    pthread_cond_signal(&buff->not_empty);
    pthread_mutex_unlock(&buff->lock);
}

int delVal(CircularBuffer *buff) {
    int item;
    int wait = 0;
    pthread_mutex_lock(&buff->lock);
    while (buff->count == 0) {
        pthread_cond_wait(&buff->not_empty, &buff->lock);
        printf("Blocked due to empty buffer\n");
        wait = 1;
    }
    if(wait == 1){
        printf("Done waiting on empty buffer\n");
        wait = 0;
    }
    item = buff->buffer[buff->out];
    buff->out = (buff->out + 1) % buff->size;
    buff->count--;
    pthread_cond_signal(&buff->not_full);
    pthread_mutex_unlock(&buff->lock);
    return item;
}

void *producer(void *args){
    int item;
    ThreadArgs *prod_args = (ThreadArgs *)args;
    int producer_id = prod_args->producer_id;
    CircularBuffer *buff = prod_args->buff;

    //Random Number Gen
    srand(time(0) + 4); //Make it slightly different from Consumer

    int numVals = (rand() % 10) + 1;
    printf("P%d: producing %d values\n", producer_id, numVals);

    for (int i = 0; i < numVals; i++) {
        item = rand() % 11;
        addVal(buff, item);
        printf("P%d: Writing %d to position %d\n", producer_id, item,  buff->in);
        usleep(1000);
    }

    //Exit
    printf("P%d: Exiting\n", producer_id);
    pthread_exit(NULL);
}

void *consumer(void *args){
    ThreadArgs *cons_args = (ThreadArgs *)args;
    int consumer_id = cons_args->consumer_id;
    CircularBuffer *buff = cons_args->buff;

    //Random Number Gen
    srand(time(0));

    int numVals = (rand() % 10) + 1;
    printf("C%d: Consuming %d values\n", consumer_id, numVals);
        for (int i = 0; i < numVals; i++) {
            int item = delVal(buff);
            printf("C%d: Reading %d from position %d\n", consumer_id, item, buff->out);
            usleep(1000);
        }

    if (producers_finished == true){
        //Exit
        printf("C%d: Exiting\n", consumer_id);
        pthread_exit(NULL);
    
    }

    //Exit
    printf("C%d: Exiting\n", consumer_id);
    pthread_exit(NULL);
}