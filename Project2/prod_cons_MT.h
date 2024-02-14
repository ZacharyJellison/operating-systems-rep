#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int* data;
    int front;
    int rear;
    int count;
    int size;
}BoundedBuffer;

void producer();    //Enqueue
void consumer();    //Dequeue

bool isFull();
bool isEmpty();

BoundedBuffer* createBuffer();
void destroyBuffer();