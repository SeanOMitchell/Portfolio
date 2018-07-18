//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 96241 ACCEPTED

#include <stdio.h>
#include <stdlib.h>

//Function declarations for the string manipulation methods
int primeNumberDetection(int noToTest);
int reverse(char *textToReverse);

//Main function of the program
int main(void) {

    char ch = 0;  //Stores the current character in the input stream
    int stringSize = 0;   //Stores the size of the inputted sring
    int capacity = 1;   //Stores the amount of memory that is available for the inputted string
    int count = 0;  //A counter for the character position in the string

    char *text = malloc(sizeof(char) * capacity);   //A pointer implementing a string that will hold the input

    //Keep getting the next character till the end of file is reached
    do{
        ch = getchar();
        //If the position of the character is not a prime number, add it to the text string
        if (primeNumberDetection(count) == 0){
            text[stringSize] = ch;
            stringSize++;
            //If the size of the string is at capacity, allocate more memory
            if(stringSize == capacity){
                capacity += 10;
                text = realloc(text,capacity * sizeof(char));
            }
        }
        count++;
    }while (ch != EOF);

    //Call function to reverse the text string
    reverse(text);

    return EXIT_SUCCESS;
}

//Function to detect if a given number is prime or not
int primeNumberDetection(int noToTest){
    int i;
    int flag = 1;
    //Divides by numbers up to half the given number, if a factor is found, set the return flag to 0
    for(i = 2; i <= noToTest/2; i++){

        if(noToTest % i == 0){
            flag = 0;
        }
    }

    return flag;
}

//Recursive function to reverse a given string, printing the characters from back end first
int reverse(char *textToReverse)
{
    //Until the end of file is reached, recursively call this function
    if(*textToReverse != EOF)
    {
        reverse(textToReverse+1);
        printf("%c", *textToReverse);
    }
}