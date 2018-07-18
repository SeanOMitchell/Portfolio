//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 118130 ACCEPTED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function declarations for the program functions
int input();
int sortOddOrEven();
int output();

int *intList;   //Array of integers to be sorted
char parityInput[5];    //Stores either "odd" or "even"
int listLength;     //The length of the array

//Main function of the program, gets a list of numbers and either sorts the even or odd components
int main(void) {
    //Records the list of numbers
    input();
    //Sorts either the odd or even elements
    sortOddOrEven();
    //Prints the sorted list
    output();
    //Clear up memory allocation
    free(intList);

}

//Reads in the list of numbers
int input(){
    //Reads the parity to sort and the number of elements
    scanf("%s", parityInput);
    scanf("%d", &listLength);

    //Allocates just enough memory for the given number of numbers
    intList = malloc(listLength * sizeof(int));

    //Read in given number of numbers
    int i;
    for(i = 0; i < listLength; i++) {
        scanf("%d", &intList[i]);
    }
}

//Either sorts the list's odd or even numbers depending on the choice that was input
int sortOddOrEven(){
    int firstNumber;    //First number to be compared
    int secondNumber;   //Second number to be compared
    int tempStore;  //Temp storage for value of a number as they are swapped
    //If the chosen parity was odd
    if(strcmp(parityInput, "odd") == 0) {
        //For each number except the last
        for(firstNumber = 0; firstNumber < listLength - 1; firstNumber++){
            //If it is an odd number
            if(intList[firstNumber] % 2 != 0) {
                //For subsequent numbers
                for (secondNumber = firstNumber + 1; secondNumber < listLength; secondNumber++) {
                    //If it is an odd number
                    if(intList[secondNumber] % 2 != 0) {
                        //If the second number is smaller than the first, swap the two
                        if(intList[secondNumber] < intList[firstNumber]){
                            tempStore = intList[secondNumber];
                            intList[secondNumber] = intList[firstNumber];
                            intList[firstNumber] = tempStore;
                        }
                    }
                }
            }
        }
    }
    //If the chosen parity was even
    else if(strcmp(parityInput, "even") == 0) {
        //For each number except the last
        for(firstNumber = 0; firstNumber < listLength - 1; firstNumber++){
            //If it is an even number
            if(intList[firstNumber] % 2 == 0) {
                //For subsequent numbers
                for (secondNumber = firstNumber + 1; secondNumber < listLength; secondNumber++) {
                    //If it is an even number
                    if(intList[secondNumber] % 2 == 0) {
                        //If the second number is smaller than the first, swap the two
                        if(intList[secondNumber] < intList[firstNumber]){
                            tempStore = intList[secondNumber];
                            intList[secondNumber] = intList[firstNumber];
                            intList[firstNumber] = tempStore;
                        }
                    }
                }
            }
        }
    }
}

//Prints the current list of numbers
int output(){
    int i;

    for(i = 0; i < listLength; i++) {
        printf("%d ", intList[i]);
    }
}