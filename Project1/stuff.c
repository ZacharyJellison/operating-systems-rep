#include <pthread.h>
#include <stdio.h>

void *myThread(){
    int ret = 42;
    return &ret;
}

int main (){
    pthread_t tid;
    void *status;
    pthread_create(&tid, NULL, myThread, NULL);
    pthread_join(tid, &status);
    printf("%d\n", *(int*)status); return 0;
}