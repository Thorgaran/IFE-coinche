/**
 * \file displayMain.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "displayMain.h"
#include "leaderboard.h"
#include "stringUtils.h"

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
    displayFrame();
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
    printf("\033[15;21H1: Play");
    printf("\033[17;21H2: AI games");
    printf("\033[19;21H3: AI settings");
    printf("\033[21;21H4: Leaderboard");
    printf("\033[23;21H5: Credits");
    printf("\033[25;21H6: Exit game");
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
        printf("\033[10E\033[6CWin a game to see your name displayed here!"); //Display placeholder message
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

void displayCredits(void) {
    char credits[][54] = {
        "Victor G. and Mathieu M.",
        "For coding",
        "The Stack Overflow community",
        "For answers to the most obscure questions",
        "F.C.",
        "For constantly criticizing (and motivating us)",
        "A.B.C.",
        "For endless debates on the best way to code",
        "...and everyone else",
        "For playtesting, coding tips, and design inputs"
    };
    char *formattedStr = NULL;
    displayFrame();
    printf("\033[2;31Hd8b   d8,");
    printf("\033[1E\033[30C88P  `8P    d8P");
    printf("\033[1E\033[29Cd88       d888888P");
    printf("\033[1E\033[2Cd8888b  88bd88b d8888b d888888    88b  ?88'   .d888b");
    printf("\033[1E\033[1Cd8P' `P  88P'  `d8b_,dPd8P' ?88    88P  88P    ?8b,");
    printf("\033[1E\033[1C88b     d88     88b    88b  ,88b  d88   88b      `?8b");
    printf("\033[1E\033[1C`?888P'd88'     `?888P'`?88P'`88bd88'   `?8b  `?888P'");
    printf("\033[1E╠═════════════════════════════════════════════════════╣");
    for (int i = 0; i < 10; i++) {
        if (i%2 == 0) { //If i is even
            printf("\033[2E\033[1C"); //Move cursor two lines down
            formattedStr = formatStr(credits[i], 53, TEXT_CENTER, TRUE); //Prepare the line, underlined
        }
        else { //If i is odd
            printf("\033[1E\033[1C"); //Move cursor one line down
            formattedStr = formatStr(credits[i], 53, TEXT_CENTER, FALSE); //Prepare the line, not underlined
        }
        printf(formattedStr); //Display the line
        free(formattedStr); //Free formattedStr, not needed anymore
    }
}