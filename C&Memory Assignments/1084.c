//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 118012 ACCEPTED

#include <stdio.h>
#include <stdlib.h>

//Function declarations for the program functions
int input();
int movementPhase();
int arrivalPhase(int stepCounter);
int output();

//Define a global structure to hold each vehicle
struct Vehicle {
    int arrivalTime;    //Time step in which the vehicle arrives to the highway
    int rowIndex;   //Vehicles assigned row
    int columnIndex;    //Vehicles current column
    char active;    //Stores whether or not the vehicle is currenly on the highway
};

int rowNumber;  //Total number of rows for the grid
int columnNumber;   //Total number of columns for the grid
int stepNumber;     //Total number of simulation steps to take
char **highway;     //Array of strings (character pointers) to be used as the highway
struct Vehicle *vehicleList;    //Array of each vehicle that was submitted
int arrivalNumber = 0;  //Number of submitted vehicles

//Main function of the program, simulates a highway and the vehicles on it for a given number of time steps
int main(void) {
    int currentRow;
    int currentColumn;

    //Gets the size of the highway, the details of the vehicles and the amount of timesteps to take
    input();

    int i;
    int stepCount;
    //For each time step, simulate one more step of the highway
    for(stepCount = 0; stepCount < stepNumber; stepCount++){
        //Vehicles on the highway move
        movementPhase();
        //Vehicles arrive on the highway
        arrivalPhase(stepCount);
    }
    //Output the final state of the highway
    output();
    //Clear up memory allocation
    free(highway);
    free(vehicleList);

}

//Read in the highway size, vehicle details and how many time steps to simulate
int input(){
    int inputArrival;   //Input number for the arrival time
    int inputRow;   //Input number for the vehicle row
    int capacity = 10;  //Current capacity of the list of vehicles
    int currentRow;     
    int currentColumn;
    //Allocates enough memory to store vehicles up to the capacity
    vehicleList = malloc(capacity * sizeof(struct Vehicle));

    //Read in the size of the highway and number of timesteps
    scanf("%d %d %d", &rowNumber, &columnNumber, &stepNumber);
    //Allocates just enough memory to store the given number of rows
    highway = malloc(rowNumber * sizeof(char *));

    int i;
    //For each row, allocate enough space to store the given number of columns
    for(i = 0; i < rowNumber; i++){
        highway[i] = malloc(columnNumber * sizeof(char));
    }

    //Populate the highway with the original state (All empty)
    for(currentRow = 0; currentRow < rowNumber; currentRow++) {
        for(currentColumn = 0; currentColumn < columnNumber; currentColumn++) {
            highway[currentRow][currentColumn] = '.';
        }
    }

    //While end of file has not been reached, keep reading input
    while(feof(stdin)==0){
        //Read in each vehicle's details
        scanf("%d %d", &inputArrival, &inputRow);
        //Stores these details and the other initial details in the correspoding vehicle in the array
        vehicleList[arrivalNumber].arrivalTime = inputArrival;
        vehicleList[arrivalNumber].rowIndex = inputRow;
        vehicleList[arrivalNumber].columnIndex = 0;
        vehicleList[arrivalNumber].active = 'n';
        //Number of vehicles increased by 1
        arrivalNumber++;
        //If the array is at capacity, increase the size of the array
        if(arrivalNumber == capacity - 1){
            capacity += 10;
            vehicleList = realloc(vehicleList, capacity * sizeof(struct Vehicle));
        }
    }
}

//Vehicles already on the highway move
int movementPhase(){
    int i;
    //For each vehicle
    for(i = 0; i < arrivalNumber - 1; i++){
        //If it is on the highway
        if(vehicleList[i].active == 'y'){
            //Remove from the current position
            highway[vehicleList[i].rowIndex][vehicleList[i].columnIndex] = '.';
            //Move its position along 1 column
            vehicleList[i].columnIndex++;
            //If it is still on the highway, add it back at its new position
            if(vehicleList[i].columnIndex != columnNumber){
                highway[vehicleList[i].rowIndex][vehicleList[i].columnIndex] = '1';
            }
            //If not, remove it from the highway
            else{
                vehicleList[i].active = 'n';
            }
        }
    }
}

//Vehicles not already on the highway get a chance to arrive
int arrivalPhase(int stepCounter){
    int i;
    //For each vehicle
    for(i = 0; i < arrivalNumber - 1; i++){
        //If the time it is supposed to arrive is the current timestep
        if(vehicleList[i].arrivalTime == stepCounter){
            //Add to the highway
            highway[vehicleList[i].rowIndex][0] = '1';
            vehicleList[i].active = 'y';
        }
        //If the vehicle's arrival time is more than the current timestep, stop checking 
        if(vehicleList[i].arrivalTime > stepCounter){
            break;
        }
    }
}

//Outputs the current state of the highway
int output(){
    int currentRow;
    int currentColumn;

    for(currentRow = 0; currentRow < rowNumber; currentRow++) {
        for(currentColumn = 0; currentColumn < columnNumber; currentColumn++) {
            printf("%c", highway[currentRow][currentColumn]);
        }
        if(currentRow != rowNumber - 1) printf("\n");
    }
}