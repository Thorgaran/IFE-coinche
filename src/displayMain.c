#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "displayMain.h"
#include "stringUtils.h"
#include "leaderboard.h"

void displayFrame(void) {
    printf("\033[1;1H"); //Move cursor to origin
    printf("╔═════════════════════════════════════════════════════╗\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("╠═════════════════════════════════════════════════════╣\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("╚═════════════════════════════════════════════════════╝");
    printf("\033[28;28H"); //Move cursor to the info box
}

void clearInfoMsg(void) {
    printf("\033[28;2H                                                     \033[1E\033[1C");
    //Move cursor to the info message box, clear the first line, move cursor to the next line
    printf("                                                     \033[27D\033[1A");
    //Clear the line, move cursor to the middle of the box
}

void displayInfoMsg(char messageLine1[], char messageLine2[]) {
    char* formattedStr;
    clearInfoMsg();
    formattedStr = formatStr(messageLine1, 53, TEXT_CENTER, FALSE); //The table is 53 characters wide
    printf("\033[28;2H%s\033[%ldD", formattedStr, (54 - strlen(messageLine1))/2);
    //Move cursor to the info message box, print the first line, move cursor to the end of message1
    free(formattedStr); //Free formattedStr as it's not needed anymore
    if (messageLine2[0] != '\0') { //If the message has a second line
        formattedStr = formatStr(messageLine2, 53, TEXT_CENTER, FALSE); //The table is 53 characters wide
        printf("\033[1E\033[1C%s\033[%ldD", formattedStr, (54 - strlen(messageLine2))/2);
        //Move cursor to the second line, print the second line of the message, move cursor to the end of message2
        free(formattedStr); //Free formattedStr as it's not needed anymore
    }
}

void resizeCmdWindow(int nbOfLines, int nbOfColumns) {
    printf("\033[8;%d;%dt", nbOfLines, nbOfColumns); //Resize the window
}

void displayMenu(void) {
    printf("\033[2;3H░█████╗░░█████╗░██╗███╗░░██╗░█████╗░██╗░░██╗███████╗");
    printf("\033[3;3H██╔══██╗██╔══██╗██║████╗░██║██╔══██╗██║░░██║██╔════╝");
    printf("\033[4;3H██║░░╚═╝██║░░██║██║██╔██╗██║██║░░╚═╝███████║█████╗░░");
    printf("\033[5;3H██║░░██╗██║░░██║██║██║╚████║██║░░██╗██╔══██║██╔══╝░░");
    printf("\033[6;3H╚█████╔╝╚█████╔╝██║██║░╚███║╚█████╔╝██║░░██║███████╗");
    printf("\033[7;3H░╚════╝░░╚════╝░╚═╝╚═╝░░╚══╝░╚════╝░╚═╝░░╚═╝╚══════╝");
    printf("\033[8;11H░██████╗░░█████╗░███╗░░░███╗███████╗");
    printf("\033[9;11H██╔════╝░██╔══██╗████╗░████║██╔════╝");
    printf("\033[10;11H██║░░██╗░███████║██╔████╔██║█████╗░░");
    printf("\033[11;11H██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░");
    printf("\033[12;11H╚██████╔╝██║░░██║██║░╚═╝░██║███████╗");
    printf("\033[13;11H░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝");
    printf("\033[14;1H╠═════════════════════════════════════════════════════╣");
    printf("\033[17;21H1. Start a game");
    printf("\033[19;21H2. Leaderboard");
    printf("\033[21;21H3. Credits");
    printf("\033[23;21H4. Exit game");
    printf("\033[28;28H"); //Move cursor to the info box
}

void displayLeaderboard(void) {
    char names[10][MAX_PLAYER_NAME_LENGTH+1];
    char *formattedName = NULL;
    int nbOfPlayers, wins[10];
    displayFrame();
    printf("\033[2;6H__            __        __                    __");
    printf("\033[1E\033[4C/ /__ ___ ____/ /__ ____/ /  ___  ___ ________/ /");
    printf("\033[1E\033[3C/ / -_) _ `/ _  / -_) __/ _ \\/ _ \\/ _ `/ __/ _  /");
    printf("\033[1E\033[2C/_/\\__/\\_,_/\\_,_/\\__/_/ /_.__/\\___/\\_,_/_/  \\_,_/");
    printf("\033[1E╠═════════════════════════════════════════════════════╣");
    nbOfPlayers = getTopTen(names, wins);
    if (nbOfPlayers == 0) { //If there are no players to display
        printf("\033[5E\033[4CWin a game to see your name displayed here!"); //Display placeholder message
    }
    else { //If there are players to display
        printf("\033[4E\033[4C╭────┬───────────────────────────────────┬────╮"); //Display the top of the table
        printf("\033[1E\033[4C│Rank│               Name                │Wins│");
        printf("\033[1E\033[4C├────┼───────────────────────────────────┼────┤");
        for (int i = 0; i < nbOfPlayers; i++) {
            formattedName = formatStr(names[i], 35, TEXT_CENTER, FALSE);
            printf("\033[1E\033[4C│ %2d │%s│ %3d│", i+1, formattedName, wins[i]);
        }
        printf("\033[1E\033[4C╰────┴───────────────────────────────────┴────╯"); //Display end of the table
    }
}