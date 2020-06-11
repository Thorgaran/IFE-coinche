#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "displayMain.h"
#include "stringUtils.h"
#include "userInput.h"
#include "play.h"

void displayFrame(void) {
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

void displayMenu(void){
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
    printf("\033[28;45H"); //Move cursor to the info box
}

void mainMenu(Player players[]){
    displayMenu();
    int chosenMenuOption = inputUserInt(1,4,"Select an action: enter its number");
    switch (chosenMenuOption){
    case 1: playGame(players);
        break;
    
    case 2: 
        displayLeaderboard();
        break;
    
    case 3: 
        displayCredits();
        break;
    
    case 4: break;
    }
}

void clearTerminal(void){
    for (int line = 2; line < 27; line++){
        printf("\033[%d;2H                                                     ",line);
    }
    printf("\033[28;2H                                                     ");
    printf("\033[1;17H═");
    printf("\033[1;39H═");
    printf("\033[6;1H║");
    printf("\033[6;55H║");
    printf("\033[11;1H║");
    printf("\033[11;55H║");
    printf("\033[14;1H║");
    printf("\033[14;55H║");
}