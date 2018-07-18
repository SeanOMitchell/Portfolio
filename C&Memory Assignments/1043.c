//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 101006 ACCEPTED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Create a constant to hold the max input string length
#define MAX_STRING_LENGTH 100

//Function declarations for the program functions
int inputFirstStringGroup();
int inputSecondStringGroup();
int findBiggestString();
int removeBiggestString();

char **stringPointerArray;  //Array of strings (character pointers)
int stringNumber1;  //Total number of strings in the first group
int stringNumber2;  //Total number of strings in the second group
int updatedStringNumber;    //Total number of strings stored in total
char inputString[MAX_STRING_LENGTH];    //Fixed length character array for storing input
char biggestString[MAX_STRING_LENGTH];  //Fixed length character array for holding largest string
int stringCount;    //Count of how many strings have been processed
int biggestIndex;   //Array index of the largest string

//Main function of the program, allows input of variable amounts of strings, sorts in order of length and prints them
int main(void) {

    //Get string inputs
    inputFirstStringGroup();
    inputSecondStringGroup();

    //Sorts and prints the strings
    int i;
    //For each string that was read in
    for(i = 0; i < stringNumber1 + stringNumber2; i++) {
        findBiggestString();
        printf("%s\n", biggestString);
        removeBiggestString();
    }

    //Clear up memory allocation
    free(stringPointerArray);
}

//Gets and stores input for first group of string
int inputFirstStringGroup(){
    //Reads number of strings to be read
    scanf("%d", &stringNumber1);
    //Allocates enough memory to store this number of strings
    stringPointerArray = malloc(stringNumber1 * sizeof(char *));
    //For every expected string, read string in, allocate enough memory to hold it, and store it
    for(stringCount = 0; stringCount < stringNumber1; stringCount++){
        scanf("%s", inputString);
        //Calculates length and allocates memory accordingly
        stringPointerArray[stringCount] = (char *)malloc((strlen(inputString) + 1));
        //Copies string into allocated memory
        strcpy(stringPointerArray[stringCount],inputString);
    }
}

//Gets and stores input for second group of string
int inputSecondStringGroup(){
    //Reads number of new strings to be read
    scanf("%d", &stringNumber2);
    //Updates memory allocation to store the updated number of strings
    updatedStringNumber = stringNumber1 + stringNumber2;
    //For every expected string, read string in, allocate enough memory to hold it, and store it
    stringPointerArray = realloc(stringPointerArray, updatedStringNumber * sizeof(char *));

    for(stringCount; stringCount < updatedStringNumber; stringCount++){
        scanf("%s", inputString);
        //Calculates length and allocates memory accordingly
        stringPointerArray[stringCount] = (char *)malloc((strlen(inputString) + 1));
        //Copies string into allocated memory
        strcpy(stringPointerArray[stringCount],inputString);
    }
}

//Finds the biggest string in the array
int findBiggestString(){
    int i;
    //Loops through each currently held string, replacing the biggest string and index if it finds a larger one
    for (i = 0; i < updatedStringNumber; i++) {
        if(strlen(stringPointerArray[i]) > strlen(biggestString)){
            //Replace old largest values
            strcpy(biggestString, stringPointerArray[i]);
            biggestIndex = i;
        }
    }
}

//Removes the largest string from the stored array and resize it to allow for further searching and sorting
int removeBiggestString(){
    int i;
    //Shifts values after the largest index, removing the largest string from the array
    for(i = biggestIndex; i < updatedStringNumber; i++){
        stringPointerArray[i] = stringPointerArray[i + 1];
    }
    //Reset the largest string variable to and "empty" state
    biggestString[0] = '\0';
    //Update amount of currently stored strings
    updatedStringNumber--;
    //If the amount of currently stored strings is at least 1, reallocate memory
    if (updatedStringNumber > 0) {
        stringPointerArray = realloc(stringPointerArray, updatedStringNumber * sizeof(char *));
    }
}
