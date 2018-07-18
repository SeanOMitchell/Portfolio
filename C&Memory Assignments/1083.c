//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 118125 WRONG ANSWER

#include <stdio.h>
#include <stdlib.h>

//Function declarations for the program functions
int input();
int movementPhase();
int moveVehicle(int vehicleIndex, int vehicleType);
int arrivalPhase(int stepCounter);
int output();

//Define a global structure to hold each vehicle
struct Vehicle {
    int arrivalTime;    //Time step in which the vehicle arrives to the highway
    int rowIndex;   //Vehicles assigned row
    int vehicleType;    //Type of vehicle
    int priority;   //Given priority of vehicle
    int columnIndex;    //Vehicles current column
    char active;    //Stores whether or not the vehicle is currenly on the highway
    int originalOrder;  //Original list index, used for keeping original order after vehicles have been sorted
};

//Sort function for use in qsort, sorts accordind to vehicle priority, then column, then row
int sortVehicles(const void* vehicle1, const void* vehicle2)
{
    //Compare priorities
    if(((struct Vehicle*)vehicle1)->priority > ((struct Vehicle*)vehicle2)->priority) return -1;
    else if(((struct Vehicle*)vehicle1)->priority < ((struct Vehicle*)vehicle2)->priority) return 1;

    //If priority is the same, compare column
    if(((struct Vehicle*)vehicle1)->columnIndex < ((struct Vehicle*)vehicle2)->columnIndex) return -1;
    else if(((struct Vehicle*)vehicle1)->columnIndex > ((struct Vehicle*)vehicle2)->columnIndex) return 1;

    //If column is the same, compare row
    if(((struct Vehicle*)vehicle1)->rowIndex < ((struct Vehicle*)vehicle2)->rowIndex) return -1;
    else if(((struct Vehicle*)vehicle1)->rowIndex > ((struct Vehicle*)vehicle2)->rowIndex) return 1;
    //Both vehicles are the same priority, order doesn't matter
    else return 0;
}

int rowNumber;  //Total number of rows for the grid
int columnNumber;   //Total number of columns for the grid
int stepNumber;     //Total number of simulation steps to take
char **highway;     //Array of strings (character pointers) to be used as the highway
struct Vehicle *vehicleList;    //Array of each vehicle that was submitted
int arrivalNumber = 0;  //Number of submitted vehicles

//Main function of the program, calls the functions to get football team stats
int main(void) {
    //Gets highway size, number of timesteps and details of each vehicle
    input();
    //Sort vehicle list according to priority
    qsort(vehicleList, arrivalNumber-1, sizeof(struct Vehicle), sortVehicles);

    int i;
    int stepCount;
    //For each time step, simulate one step of the highway
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

//Moves the vehicle one position on the highway, if possible and removes if it leaves the highway
int moveVehicle(int vehicleIndex, int vehicleType){
    char charType = '.';
    //Converts vehicle type from an int to a char
    if(vehicleType == 1){
        charType = '1';
    }
    else if(vehicleType == 2){
        charType = '2';
    }
    else if(vehicleType == 3){
        charType = '3';
    }
    //If the vehicle is on the highway
    if(vehicleList[vehicleIndex].active == 'y') {
        //Remove from the current position
        highway[vehicleList[vehicleIndex].rowIndex][vehicleList[vehicleIndex].columnIndex] = '.';
        //Move its position along 1 column
        vehicleList[vehicleIndex].columnIndex++;
        //If it is still on the highway
        if (vehicleList[vehicleIndex].columnIndex != columnNumber) {
            //If the current position isn't occupied, add it back to the highway
            if (highway[vehicleList[vehicleIndex].rowIndex][vehicleList[vehicleIndex].columnIndex] == '.') {
                highway[vehicleList[vehicleIndex].rowIndex][vehicleList[vehicleIndex].columnIndex] = charType;
            }
            //If the current position is occupied, move it back 1 column and add it back to the highway
            else {
                vehicleList[vehicleIndex].columnIndex--;
                highway[vehicleList[vehicleIndex].rowIndex][vehicleList[vehicleIndex].columnIndex] = charType;
            }
        //If no longer on the highway, deactivate vehicle and don't add it back to the highway
        } else if (vehicleList[vehicleIndex].columnIndex == columnNumber) {
            vehicleList[vehicleIndex].active = 'n';
        }
    }
}

//Read in the highway size, vehicle details and how many time steps to simulate
int input(){
    int inputArrival;   //Input number for the arrival time
    int inputRow;   //Input number for the vehicle row
    int inputVehicleType;   //Input number for the vehicle type
    int inputPriority;  //Input number for the vehicle priority
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

    int result;
    //While end of file has not been reached, keep reading input
    do{
        //Read in each vehicle's details
        result = scanf("%d %d %d %d", &inputArrival, &inputRow, &inputVehicleType, &inputPriority);
        //Stores these details and the other initial details in the correspoding vehicle in the array
        vehicleList[arrivalNumber].arrivalTime = inputArrival;
        vehicleList[arrivalNumber].rowIndex = inputRow;
        vehicleList[arrivalNumber].vehicleType = inputVehicleType;
        vehicleList[arrivalNumber].priority = inputPriority;
        vehicleList[arrivalNumber].columnIndex = 0;
        vehicleList[arrivalNumber].active = 'n';
        vehicleList[arrivalNumber].originalOrder = arrivalNumber;
        //Number of vehicles increased by 1
        arrivalNumber++;
        //If the array is at capacity, increase the size of the array
        if(arrivalNumber == capacity - 1){
            capacity += 10;
            vehicleList = realloc(vehicleList, capacity * sizeof(struct Vehicle));
        }

    }while (result != EOF);
}

//Vehicles already on the highway move
int movementPhase(){
    int i;
    //For each vehicle
    for(i = 0; i < arrivalNumber - 1; i++){
        //If it is on the highway
        if(vehicleList[i].active == 'y'){
            //Depending on type, attempt to move given number of spaces
            if(vehicleList[i].vehicleType == 1){
                moveVehicle(i, vehicleList[i].vehicleType);
                moveVehicle(i, vehicleList[i].vehicleType);
                moveVehicle(i, vehicleList[i].vehicleType);
            }
            else if(vehicleList[i].vehicleType == 2){
                moveVehicle(i, vehicleList[i].vehicleType);
            }
            else if(vehicleList[i].vehicleType == 3) {
                moveVehicle(i, vehicleList[i].vehicleType);
                moveVehicle(i, vehicleList[i].vehicleType);
            }
        }
    }
}

//Vehicles not already on the highway get a chance to arrive
int arrivalPhase(int stepCounter){
    int currentRow;

    int i;
    //For each row
    for(currentRow = 0; currentRow < rowNumber; currentRow++){
        int earliestArrivalPosition = arrivalNumber - 1;    //Position of the earliest arrival in the original list / order
        int earliestArrivalIndex = 0;   //Position of the earliest arrival in the sorted vehicle list
        //For each vehicle
        for(i = 0; i < arrivalNumber - 1; i++){
            //If the time is when it is supposed to arrive, and the row is the correct arrival row
            if(vehicleList[i].arrivalTime == stepCounter && vehicleList[i].rowIndex == currentRow){
                //If the vehicle was before the current earliest vehicle in the original order
                if(vehicleList[i].originalOrder < earliestArrivalPosition){
                    //Store array position of the new earliest vehicle
                    earliestArrivalIndex = i;
                }
            }
        }
        //If the earliest vehicle is supposed to arrive at this time (Needed due to initialising variable)
        if(vehicleList[earliestArrivalIndex].arrivalTime == stepCounter) {
            //Add vehicle to the highway
            if (vehicleList[earliestArrivalIndex].vehicleType == 1) {
                highway[vehicleList[earliestArrivalIndex].rowIndex][0] = '1';
            } else if (vehicleList[earliestArrivalIndex].vehicleType == 2) {
                highway[vehicleList[earliestArrivalIndex].rowIndex][0] = '2';
            } else if (vehicleList[earliestArrivalIndex].vehicleType == 3) {
                highway[vehicleList[earliestArrivalIndex].rowIndex][0] = '3';
            }
            //Activate vehicle
            vehicleList[earliestArrivalIndex].active = 'y';
        }
    }
}

//Prints current highway state
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