//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 101021 ACCEPTED

#include <stdio.h>
#include <stdlib.h>

//Function declarations for the program functions
int input();
int simulateStep();
int output();

int rowNumber;  //Total number of rows for the grid
int columnNumber;   //Total number of columns for the grid
int stepNumber;     //Total number of simulation steps to take
char **gameBoard;   //Array of strings (character pointers) to be used as the grid
char **nextStepGameBoard;   //Another grid to be used to store the results of each step so as to not disrupt the original grid while calculating

//Main function of the program, reads in a grid and executes the game of life on it a given number of times
int main(void) {
    //Reads input values for the grid
    input();
    //Iterates the game of life steps for the given number of times
    int stepCount;
    for(stepCount = 0; stepCount < stepNumber; stepCount++){
        simulateStep();
    }
    //Output the final resulted grid state
    output();
    //Clear up memory allocation
    free(gameBoard);
    free(nextStepGameBoard);
}

//Reads in the grid size, number of iterations and initial board state
int input(){
    int currentRow;
    int currentColumn;

    //Read row number, column number and step number respectively
    scanf("%d %d %d", &rowNumber, &columnNumber, &stepNumber);
    //Allocates enough memory to the two grids, to store the given number of rows
    gameBoard = malloc(rowNumber * sizeof(char *));
    nextStepGameBoard = malloc(rowNumber * sizeof(char *));

    //For each row in each grid, allocate enough memory to store the given number of columns
    for(currentRow = 0; currentRow < rowNumber; currentRow++){
        gameBoard[currentRow] = malloc(columnNumber * sizeof(char));
        nextStepGameBoard[currentRow] = malloc(columnNumber * sizeof(char));
    }

    //For each position on the grid, read in the given initial value and store it in both grids
    for(currentRow = 0; currentRow < rowNumber; currentRow++){
        for(currentColumn = 0; currentColumn < columnNumber; currentColumn++){
            do{
                scanf("%c", &gameBoard[currentRow][currentColumn]);
                nextStepGameBoard[currentRow][currentColumn] = gameBoard[currentRow][currentColumn];
            }while(gameBoard[currentRow][currentColumn] == '\n');
        }
    }
}

//Uses the rules of the game of life to simulate a time step
int simulateStep(){
    int currentRow;
    int currentColumn;
    int aliveNeighbours;    //Number of surrounding cells that are alive

    //For each position on the first grid, look at the surrounding cells and count how many neighbours it has that are alive
    for (currentRow = 0; currentRow < rowNumber; currentRow++){
        for (currentColumn = 0; currentColumn < columnNumber; currentColumn++){
            //Starts checks, resets alive neighbour counter
            aliveNeighbours = 0;
            //If the position is not on the top row or left column
            if(currentRow != 0 && currentColumn != 0){
                //Check top left neighbour
                if(gameBoard[currentRow-1][currentColumn-1] == 'X') aliveNeighbours++;
            }
            //If the position is not on the top row
            if(currentRow != 0){
                //Check top neighbour
                if(gameBoard[currentRow-1][currentColumn] == 'X') aliveNeighbours++;
            }
            //If the position is not on the top row or right column
            if(currentRow != 0 && currentColumn != columnNumber-1){
                //Check top right neighbour
                if(gameBoard[currentRow-1][currentColumn+1] == 'X') aliveNeighbours++;
            }
            //If the position is not on the left column
            if(currentColumn != 0){
                //Check left neighbour
                if(gameBoard[currentRow][currentColumn-1] == 'X') aliveNeighbours++;
            }
            //If the position is not on the right column
            if(currentColumn != columnNumber-1){
                //Check right neighbour
                if(gameBoard[currentRow][currentColumn+1] == 'X') aliveNeighbours++;
            }
            //If the position is not on the bottom row or left column
            if(currentRow != rowNumber-1 && currentColumn != 0){
                //Check bottom left neighbour
                if(gameBoard[currentRow+1][currentColumn-1] == 'X') aliveNeighbours++;
            }
            //If the position is not on the bottom row
            if(currentRow != rowNumber-1){
                //Check bottom neighbour
                if(gameBoard[currentRow+1][currentColumn] == 'X') aliveNeighbours++;
            }
            //If the position is not on the bottom row or right column
            if(currentRow != rowNumber-1 && currentColumn != columnNumber-1){
                //Check bottom right neighbour
                if(gameBoard[currentRow+1][currentColumn+1] == 'X') aliveNeighbours++;
            }

            //Depending on the amount of alive neighbours, change position state of the next step grid to be alive or dead
            if(aliveNeighbours < 2) nextStepGameBoard[currentRow][currentColumn] = '.';
            else if(aliveNeighbours > 3) nextStepGameBoard[currentRow][currentColumn] = '.';
            else if(aliveNeighbours == 3) nextStepGameBoard[currentRow][currentColumn] = 'X';
        }
    }

    //Match the first grid to the now fully updated one
    for(currentRow = 0; currentRow < rowNumber; currentRow++){
        for(currentColumn = 0; currentColumn < columnNumber; currentColumn++){
            gameBoard[currentRow][currentColumn] = nextStepGameBoard[currentRow][currentColumn];
        }
    }
}

//prints the current grid state
int output(){
    int currentRow;
    int currentColumn;

    //Prints each position on the grid in the grid format
    for (currentRow = 0; currentRow < rowNumber; currentRow++) {
        for (currentColumn = 0; currentColumn < columnNumber; currentColumn++) {
            printf("%c", gameBoard[currentRow][currentColumn]);
        }
        if(currentRow != rowNumber - 1) printf("\n");
    }
}