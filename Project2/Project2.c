#include "prod_cons_MT.c"


//Global Variables


int main(int argc, char **argv){

    //Take command Line Input
    int size = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    CircularBuffer buff;
    init_buffer(&buff, size, num_producers, num_consumers);
    pthread_t producer_thread[num_producers], consumer_thread[num_consumers];

    //New Producer Created
    for(int i = 0; i < num_producers; i++){
        printf("Main: started producer %d\n", i);
        pthread_create(&producer_thread[i], NULL, producer, &buff);
    }

    //New Consumer Created
    for(int k = 0; k < num_consumers; k++){
        printf("Main: started consumer %d\n", k);
        pthread_create(&consumer_thread[k], NULL, consumer, &buff);
    }

    //Wait for threads
    for (int m = 0; m < num_producers; m++) 
	    pthread_join(producer_thread[m], NULL);

    for (int n = 0; n < num_consumers; n++) 
	    pthread_join(consumer_thread[n], NULL);

    //Finish
    printf("Main: program completed\n");
    return 0;
}