#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

//*****Function Declerations*****
void stackprint();
void queueprint();
void listprint();


int main(int argc, char **argv){
//*****Reference for reading file input https://stackoverflow.com/questions/20378430/reading-numbers-from-a-text-file-into-an-array-in-c


//Read Data From File to an Array for Easy access
    FILE *fp = fopen(argv[1], "r");

//Turn file inputs into an Array of length 10
    const unsigned MAX_LENGTH = 10;
    int arr[MAX_LENGTH];

    for(int loop = 0; loop < MAX_LENGTH; loop++){
        fscanf(fp, "%d", &arr[loop]);
    }

    fclose(fp);
//End File Read


//Functions to print the 3 data types
    stackprint(&arr);
    //queueprint(&arr);
    //listprint(&arr);

    return 0;
}


//*****Function Definitions*****

//Prints Last to First
void stackprint(int SinpArray[]){
//Move Inputs from array to Data Structure

//Print Contents
    for(int i = 0; i < 10; i++){
        printf("%d ", SinpArray[i]);
    }
    printf("\n");

}


//Prints First to Last
void queueprint(int QinpArray[]){
//Move Inputs from array to Data Structure

//Print Contents
    for(int i = 10; i > 0; i--){
        printf("%d ", QinpArray[i-1]);
    }
    printf("\n");
}


//Prints in Numerical order (Smalled to Largest)
void listprint(int LinpArray[]){
//Move Inputs from array to Data Structure

//Print Contents
    for(int i = 0; i < 10; i++){
        printf("%d ", LinpArray[i]);
    }
    printf("\n");
}


//********** IMPLEMENTING THE STACK **********
//Reference: https://stackoverflow.com/questions/71717509/im-trying-to-create-a-stack-in-c-using-structures-but-my-push-function-doesnt

typedef struct stack
{
    int top;
    int items[STACK_SIZE];
}
STACK;

static void push(STACK* st, int newitem){
    st->items[st->top++] = newitem;
}

static void pop(STACK* st){
    int out = st->items[st->top];
    printf("%d ", out);
}