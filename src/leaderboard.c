#include <stdio.h>
#include <string.h>
#include "leaderboard.h"

void writeLine(FILE *leaderboard, char playerName[], int wins) {
    fprintf(leaderboard, "%s;%3d;%2ld\n", playerName, wins, strlen(playerName)+8); //Write the line
}

void increaseWins(char playerName[]) {
    FILE *leaderboard;
    char *fgetsReturnPtr = NULL;
    char line[MAX_PLAYER_NAME_LENGTH+8], name[MAX_PLAYER_NAME_LENGTH+1], nameAbove[MAX_PLAYER_NAME_LENGTH+1];
    int wins = 0, lineLength = 0, winsAbove = 0, lineLengthAbove = 0;
    leaderboard = fopen("leaderboard.txt", "r+");       //Open the file leaderboard.txt in read-write mode
    if (leaderboard == NULL) {                          //If the file wasn't found,
        leaderboard = fopen("leaderboard.txt", "w");    //create it in write-only mode
    }
    else
    {
        do {
            fgetsReturnPtr = fgets(line, MAX_PLAYER_NAME_LENGTH + 9, leaderboard);  //Try to read a line in the file
            if (fgetsReturnPtr != NULL) {                                           //If the fgets function did read a line (it didn't reach the end of the file)
                sscanf(line, "%[^;];%3d;%2d", name, &wins, &lineLength);            //Parse the obtained line: name;wins   ;lineLength\n
            }
        } while ((fgetsReturnPtr != NULL) && (strcmp(playerName, name) != 0));
        //While the file pointer hasn't reached the end of the file AND the read name isn't playerName
    }
    if (fgetsReturnPtr == NULL) {               //If the player wasn't found in the file
        writeLine(leaderboard, playerName, 1);  //Append a new line for this player at the end of the file
    }
    else {                                              //If the player was found in the file
        wins++;                                         //Increment the number of wins
        fseek(leaderboard, -7, SEEK_CUR);               //Move to the player's number of wins
        fprintf(leaderboard, "%3d", wins);              //Write the new number of lines
        fseek(leaderboard, -(lineLength-4), SEEK_CUR);  //Move to the start of the player line
        while ((ftell(leaderboard) > 0) && (wins > winsAbove)) {
        //While the cursor hasn't reached the start of the file, AND the player above has less wins than the current player
            fseek(leaderboard, -3, SEEK_CUR);                                       //Move to the lineLength number of the above line
            if (ftell(leaderboard) > 0) {                                           //If the player isn't already the top player
                fgets(line, 3, leaderboard);                                        //Get the line length in a string
                sscanf(line, "%2d", &lineLengthAbove);                              //Parse the string to save the line length
                fseek(leaderboard, -(lineLengthAbove - 1), SEEK_CUR);               //Move to the start of the line
                fgets(line, MAX_PLAYER_NAME_LENGTH + 9, leaderboard);               //Read the full line
                sscanf(line, "%[^;];%3d", nameAbove, &winsAbove);                   //Parse the obtained line: name;wins
                if (wins > winsAbove) {                                             //If the player has more wins now than the player above, swap lines
                    fseek(leaderboard, -lineLengthAbove, SEEK_CUR);                 //Move to the start of the line
                    writeLine(leaderboard, name, wins);                             //Write the player line first
                    writeLine(leaderboard, nameAbove, winsAbove);                   //Write the above player line next
                    fseek(leaderboard, -(lineLength + lineLengthAbove), SEEK_CUR);  //Move to the end of the line above the player' line
                }
            }
        }
    }
    fclose(leaderboard); //Close the leaderboard file
}

int getTopTen(char names[][MAX_PLAYER_NAME_LENGTH+1], int wins[]) {
    FILE *leaderboard;
    char *fgetsReturnPtr = NULL;
    char line[MAX_PLAYER_NAME_LENGTH+8];
    int nbOfPlayers = 0;
    leaderboard = fopen("leaderboard.txt", "r"); //Open the file leaderboard.txt in read-only mode
    if (leaderboard != NULL) { //If the file was found (thus contains at least one line)
        do {
            fgetsReturnPtr = fgets(line, MAX_PLAYER_NAME_LENGTH + 9, leaderboard);  //Try to read a line in the file
            if (fgetsReturnPtr != NULL) {                                           //If the fgets function did read a line (it didn't reach the end of the file)
                sscanf(line, "%[^;];%3d", names[nbOfPlayers], &wins[nbOfPlayers]);     //Parse the obtained line: name;wins
                nbOfPlayers++;                                                        //Increment the number of lines
            }
        } while ((fgetsReturnPtr != NULL) && (nbOfPlayers < 10));
        //While the file pointer hasn't reached the end of the file AND it has read less than 10 lines
    }
    return nbOfPlayers;
}