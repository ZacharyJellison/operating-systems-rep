#include "prod_cons_MT.c"


//Global Variables
extern bool producers_finished;


int main(int argc, char **argv){

    //Take command Line Input
    int size = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    CircularBuffer buff;
    init_buffer(&buff, size);
    pthread_t producer_thread[num_producers], consumer_thread[num_consumers];
    ThreadArgs producer_args[num_producers], consumer_args[num_consumers];

    //New Producer Created
    for(int i = 0; i < num_producers; i++){
        printf("Main: started producer %d\n", i);
        producer_args[i].producer_id = i;
        producer_args[i].buff = &buff;
        pthread_create(&producer_thread[i], NULL, producer, &producer_args[i]);
    }

    //New Consumer Created
    for(int k = 0; k < num_consumers; k++){
        printf("Main: started consumer %d\n", k);
        consumer_args[k].consumer_id = k;
        consumer_args[k].buff = &buff;
        pthread_create(&consumer_thread[k], NULL, consumer, &consumer_args[k]);
    }

    //Wait for threads
    for (int m = 0; m < num_producers; m++){
	    pthread_join(producer_thread[m], NULL);
        printf("MAIN: producer %d joined\n", 0);
    }

    producers_finished = true;

    for (int n = 0; n < num_consumers; n++){
	    pthread_join(consumer_thread[n], NULL);
        printf("MAIN: consumer %d joined\n", 0);
    }

    //Finish
    printf("Main: program completed\n");
    return 0;
}