//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 96239 ACCEPTED


#include <stdio.h>
#include <stdlib.h>

//Function declarations for the input and output functions
int input(int *mark, int *greaterEqual85, int *between60And84, int *lessThan60);
int output(int *greaterEqual85, int *between60And84, int *lessThan60);

//Main function of the program, counts how many exam marks fall within certain boundaries
int main(void) {

    int mark = 100;     //The exam mark that is entered
    int greaterEqual85 = 0;     //Count for marks over or equal to 85
    int between60And84 = 0;     //Count for marks between 60 and 84
    int lessThan60 = 0;     //Count for marks less than 60
    
    //Call the input function, and pass the mark and tracking variables to it
    input(&mark, &greaterEqual85, &between60And84, &lessThan60);
    
    //Call the output function, and pass the mark and tracking variables to it
    output(&greaterEqual85, &between60And84, &lessThan60);

    return EXIT_SUCCESS;
}

//Function for recieving input of a list of exam marks
int input(int *mark, int *greaterEqual85, int *between60And84, int *lessThan60){
    //While still recieving new marks
    while ((*mark) != 0) {
        scanf("%d", &(*mark));
        //Sorts marks into catagories and increments the counters
        if((*mark) == 0){
            break;
        }
        else if((*mark) >= 85){
            (*greaterEqual85) += 1;
        }
        else if((*mark) < 60){
            (*lessThan60) += 1;
        }
        else{
            (*between60And84) += 1;
        }
    }
}

//Function for printing the counters for the various bands of exam marks
int output(int *greaterEqual85, int *between60And84, int *lessThan60){
    printf(">=85:%d\n", (*greaterEqual85));
    printf("60-84:%d\n", (*between60And84));
    printf("<60:%d\n", (*lessThan60));
}
