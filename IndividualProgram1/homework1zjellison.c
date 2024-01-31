#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10         //Number of values being sorted

//*****Function Declerations*****
void stackprint();
void queueprint();
void listprint();
//STACK FUNCTIONS
static void push();
static void pop();
//QUEUE FUNCTIONS
static void enqueue();
static void dequeue();
//LINKED LIST FUNCTIONS
void pushLL();
void sortedInsert();
void insertionSort();
void printlist();

//**********  IMPLEMENTING THE STACK  **********
//Reference: https://stackoverflow.com/questions/71717509/im-trying-to-create-a-stack-in-c-using-structures-but-my-push-function-doesnt

typedef struct stack
{
    int top;
    int items[MAX_SIZE];
}
STACK;

static void push(STACK* st, int newitem){
    st->items[st->top++] = newitem;
}

static void pop(STACK* st){
    int out = st->items[st->top - 1];
    printf("%d ", out);
    st->top -= 1;
}

//**********  IMPLEMENTING THE QUEUE **********

typedef struct queue
{
    int rear;
    int itemsq[MAX_SIZE];
}
QUEUE;

static void enqueue(QUEUE* q, int newitemq){
    q->itemsq[q->rear--] = newitemq;
}

static void dequeue(QUEUE* q){
    int qout = q->itemsq[q->rear];
    printf("%d ", qout);
    q->rear -= 1;
}

//********** IMPLEMENTING THE LINKED LIST **********
//Sorting Algorithm of Linked List https://www.geeksforgeeks.org/sorting-a-singly-linked-list/
struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *sorted = NULL;

void pushLL(int val){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = val;
    newnode->next = head;
    head = newnode;
    
}

void sortedInsert(struct node* newnode){
    if (sorted == NULL || sorted->data >= newnode->data){
        newnode->next = sorted;
        sorted = newnode;
    }
    else{
        struct node* current = sorted;
        
        while (current->next != NULL && current->next->data < newnode->data){
            current = current->next;
        }

        newnode->next = current->next;
        current->next = newnode;
    }
}

void insertionSort(){
    struct node* current = head;
    
    while (current != NULL){
        struct node* next = current->next;
        sortedInsert(current);
        current = next;
    }

    head = sorted;
}

void printlist(){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
}

int main(int argc, char **argv){
//*****Reference for reading file input https://stackoverflow.com/questions/20378430/reading-numbers-from-a-text-file-into-an-array-in-c

//Read Data From File to an Array for Easy access
    FILE *fp = fopen(argv[1], "r");

//Turn file inputs into an Array of length 10
    int arr[MAX_SIZE];

    for(int loop = 0; loop < MAX_SIZE; loop++){
        fscanf(fp, "%d", &arr[loop]);
    }

    fclose(fp);
//End File Read


//Functions to print the 3 data types
    printf("QUEUE CONTENTS:\n");
    queueprint(&arr);
    printf("STACK CONTENTS:\n");
    stackprint(&arr);
    printf("LIST CONTENTS\n");
    listprint(&arr);

    return 0;
}




//*****Function Definitions*****

//Prints Last to First
void stackprint(int SinpArray[]){
//Move Inputs from array to Data Structure
    STACK st;
    st.top = 0;

    for(int k = 0; k < 10; k++){
        push(&st, SinpArray[k]);
    }

//Print Contents
    for(int i = 0; i < 10; i++){
        pop(&st);
    }
    printf("\n");

}


//Prints First to Last
void queueprint(int QinpArray[]){
//Move Inputs from array to Data Structure
    QUEUE q;
    q.rear = MAX_SIZE - 1;

    for(int k = 0; k < 10; k++){
        enqueue(&q, QinpArray[k]);
    }

//Print Contents
    q.rear = MAX_SIZE - 1;
    for(int i = 0; i < 10; i++){
        dequeue(&q);
    }
    printf("\n");
}


//Prints in Numerical order (Smalled to Largest)
void listprint(int LinpArray[]){
//Move Inputs from array to Data Structure
    for(int i = 0; i < 10; i++){
        pushLL(LinpArray[i]);
    }

//Print Contents
    insertionSort(head);
    printlist(head);
    printf("\n");
}