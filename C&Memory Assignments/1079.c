//Sean Mitchell
//The university of Liverpool
//201155022
//Online Judge run ID: 96242 ACCEPTED

#include <stdio.h>
#include <stdlib.h>

//Create a constant to hold the max number of teams
#define MAX_TEAMS 30

//Function declarations for the input and output functions
int input();
int output();

//Define a global structure to hold each team's details
struct Team {
    double totalGames;  //Total games played by the team
    double homeGames;   //Games played by the team at home
    double totalWins;   //Total amount of won games
    double homeWins;    //Games won by the team at home
    double goalDiff;    //Counter of the difference of goals between this team and their opponents totalled through all matches
};

//Create an array of team structures
struct Team teams[MAX_TEAMS];

//Main function of the program, calls the functions to get football team stats
int main(void) {

    //Call the input function
    input();
    //Call the output function
    output();

    return EXIT_SUCCESS;
}

//Function for recieving input of the results of a series of football matches
int input(){

    //Read in the amount of matches that were played
    int matchNo;
    scanf("%d", &matchNo);

    int homeTeamId;     //ID of the home team
    int awayTeamId;     //ID of the away team
    int homeGoals;  //Goals scored by the home team
    int awayGoals;  //Goals scored by the away team

    //Loop through each match played, reading the match information and incrementing the corresponding counters for each team
    for(int i = 0; i < matchNo; i++){
        scanf("%d %d %d %d", &homeTeamId, &awayTeamId, &homeGoals, &awayGoals);
        //Games played
        teams[homeTeamId].totalGames++;
        teams[homeTeamId].homeGames++;
        teams[awayTeamId].totalGames++;
        //Games won
        if(homeGoals > awayGoals){
            teams[homeTeamId].totalWins++;
            teams[homeTeamId].homeWins++;
        }
        else if(awayGoals > homeGoals){
            teams[awayTeamId].totalWins++;
        }
        //Goal differences
        teams[homeTeamId].goalDiff += (homeGoals - awayGoals);
        teams[awayTeamId].goalDiff += (awayGoals - homeGoals);
    }
}

//Function for printing information about each team that played at least once 
int output(){

    double winRatio;    //Ratio of wins to games played
    double homeWinRatio;    //Ratio of wins to games played at home
    double averageGoalDiff;     //Average difference in goals from all matches

    //Loop through each team, printing details if they played at least 1 match
    for(int i = 0; i < 30; i++){
        if(teams[i].totalGames != 0){
            winRatio = teams[i].totalWins / teams[i].totalGames;
            homeWinRatio = teams[i].homeWins / teams[i].homeGames;
            averageGoalDiff = teams[i].goalDiff / teams[i].totalGames;
            if (teams[i].homeGames == 0){
                printf("%d %.3f -1 %.3f \n", i, winRatio, averageGoalDiff);
            } else{
                printf("%d %.3f %.3f %.3f \n", i, winRatio, homeWinRatio, averageGoalDiff);
            }
        }
    }
}