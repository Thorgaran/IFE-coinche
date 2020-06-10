#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "displayMain.h"
#include "stringUtils.h"

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