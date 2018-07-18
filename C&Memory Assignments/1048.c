//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 118135 ACCEPTED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function declarations for the program functions
int monthStringToInt(char *monthString);
int input();
int searchAndPrintDate();
int output();

//Define a global structure to hold each date
struct Date {
    char *month;  //Month in english
    int monthNo;    //Month as a number
    int day;
    int year;
};

//Sort function for use in qsort and bsearch, sorts according to year, then month then day in descending order
int compareDates(const void* date1, const void* date2)
{
    //If one year is before 2000 and the other isn't, determine which is chronologically first
    if(((struct Date*)date1)->year >= 90 && ((struct Date*)date2)->year <= 12){
        return 1;
    }
    else if(((struct Date*)date1)->year <= 12 && ((struct Date*)date2)->year >= 90){
        return -1;
    }
    //If both years are pre-2000 or 2000 onwards, etermine which is chronilogically first
    else{
        if(((struct Date*)date1)->year < ((struct Date*)date2)->year) return 1;
        else if(((struct Date*)date1)->year > ((struct Date*)date2)->year) return -1;
    }

    //If year is the same, compare months
    if(((struct Date*)date1)->monthNo < ((struct Date*)date2)->monthNo) return 1;
    else if(((struct Date*)date1)->monthNo > ((struct Date*)date2)->monthNo) return -1;

    //If month is the same, compare days
    if(((struct Date*)date1)->day < ((struct Date*)date2)->day) return 1;
    else if(((struct Date*)date1)->day > ((struct Date*)date2)->day) return -1;
    //Both dates are the same, order doesn't matter
    else return 0;
}

struct Date *dateList;  //Array of dates
struct Date searchKey;  //Date that will be used as a key to search
int nNumber;    //n number of dates to be input

//Main function of the program, calls the functions to get football team stats
int main(void) {
    //Reads input values for the dates
    input();
    //Sorts the array of dates into chronological order
    qsort(dateList, nNumber, sizeof(struct Date), compareDates);
    //Output the sorted list of dates
    output();
    //Search for and print the answer to the given search
    searchAndPrintDate();
    //Clear up memory allocation
    free(dateList);
}

//Reads in each date to the array
int input(){
    char monthInput[10];    //Input buffer for english months
    int monthInputNo;   //Input number for month number
    int dayInput;   //Input number for month day
    int yearInput;  //Input number for month year

    //Reads number of dates
    scanf("%d", &nNumber);
    //Allocate just enough memory for given number of dates
    dateList = malloc(nNumber * sizeof(struct Date));

    int i;
    //For the given number of times, read in each date
    for(i = 0; i < nNumber; i++) {
        scanf("%s %d %d", monthInput, &dayInput, &yearInput);
        //Pass these values to the corresponding date in the array
        dateList[i].month = (char *) malloc((strlen(monthInput) + 1));  //Allocate just enough memory for the given month
        strcpy(dateList[i].month, monthInput);
        dateList[i].monthNo = monthStringToInt(monthInput);
        dateList[i].day = dayInput;
        dateList[i].year = yearInput;
    }

    //Read in the date to search for and store
    scanf("%d %d %d", &dayInput, &monthInputNo, &yearInput);
    searchKey.day = dayInput;
    searchKey.monthNo = monthInputNo;
    searchKey.year = yearInput;
}

//Print the current list of dates
int output(){
    int i;
    for(i = 0; i < nNumber; i++) {
        printf("%s %d %02d\n", dateList[i].month, dateList[i].day, dateList[i].year);
    }
}

//Uses a binary search to search for the given date in the array and then prints it out
int searchAndPrintDate(){
    struct Date *searchResult = bsearch(&searchKey, dateList, nNumber, sizeof(struct Date), compareDates);

    //If search found the date
    if(searchResult != NULL)
    {
        printf("Yes");
    }
    //If not
    else
    {
        printf("No");
    }
}

//Takes a given month as a string and returns the integer position of that month in the calender
int monthStringToInt(char *monthString){
    if(strcmp(monthString, "January") == 0){
        return 1;
    }
    else if(strcmp(monthString, "February") == 0){
        return 2;
    }
    else if(strcmp(monthString, "March") == 0){
        return 3;
    }
    else if(strcmp(monthString, "April") == 0){
        return 4;
    }
    else if(strcmp(monthString, "May") == 0){
        return 5;
    }
    else if(strcmp(monthString, "June") == 0){
        return 6;
    }
    else if(strcmp(monthString, "July") == 0){
        return 7;
    }
    else if(strcmp(monthString, "August") == 0){
        return 8;
    }
    else if(strcmp(monthString, "September") == 0){
        return 9;
    }
    else if(strcmp(monthString, "October") == 0){
        return 10;
    }
    else if(strcmp(monthString, "November") == 0){
        return 11;
    }
    else if(strcmp(monthString, "December") == 0){
        return 12;
    }
}