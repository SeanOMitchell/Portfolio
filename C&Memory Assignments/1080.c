//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 101019 ACCEPTED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Function declarations for the program functions
int input();
int calculateVectorLength();
int output();

int *vectorElements;    //Array of integers to store the elements of the vector
int nNumber;    //number of elements in the vector
double vectorLength;    //Length / norm of the vector

//Main function of the program, reads in a vector and normalises it
int main(void) {
    vectorLength = 0;

    //Reads input values for the vector
    input();
    //Calculates the norm of the vector
    calculateVectorLength();
    //Prints the normalised vector elements
    output();
    //Clear up memory allocation
    free(vectorElements);
}

//Reads in the length of the vector, then each element
int input(){
    int inputNumber;    //Used for storing the element value as it is input

    //Reads number of elements
    scanf("%d", &nNumber);
    //Allocates enough memory for this number
    vectorElements = malloc(nNumber * sizeof(int));
    int i;
    //For every element, read in the value and store it
    for(i = 0; i < nNumber; i++){
        scanf("%d", &inputNumber);
        vectorElements[i] = inputNumber;
    }
}

//Calculates the norm of the vector
int calculateVectorLength(){
    int i;
    //Squares each element and adds it to the total length
    for(i = 0; i < nNumber; i++){
        vectorLength += vectorElements[i] * vectorElements[i];
    }
    //Square roots the length to find the final length / norm
    vectorLength = sqrt(vectorLength);
}

//Prints the normalised value of each element
int output(){
    int i;
    //For each element, print the normalised value to  decimal places
    for(i = 0; i < nNumber; i++){
        if (i == nNumber-1) {
            printf("%.3f", (vectorElements[i] / vectorLength));
        }
        //If it is the last element, do not print a trailing new line
        else{
            printf("%.3f ", (vectorElements[i]/vectorLength));
        }
    }
}