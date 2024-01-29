#include <stdio.h>

void stackprint();

int main(int argc, char **argv){
//Reference for reading file input https://stackoverflow.com/questions/20378430/reading-numbers-from-a-text-file-into-an-array-in-c

//Read Data From File to an Array for Easy access
    FILE *fp = fopen(argv[1], "r");

//Turn file inputs into an Array of length 10
    const unsigned MAX_LENGTH = 10;
    int arr[MAX_LENGTH];

for(int loop = 0; loop < MAX_LENGTH; loop++){
    fscanf(fp, "%d", &arr[loop]);
}

    fclose(fp);


//Functions to print the 3 data types
    stackprint(arr);
    //queueprint(arr);
    //listprint(arr);

    return 0;
}


void stackprint(int SinpArray[]){
//Move Inputs from array to Data Structure

//Print Contents
for(int i; i < 10; i++){
    printf("%d ", SinpArray[i]);
    }
}

/*
void queueprint(int QinpArray[]){
//Move Inputs from array to Data Structure

//Print Contents

}


void listprint(int LinpArray[]){
//Move Inputs from array to Data Structure

//Print Contents

}
*/