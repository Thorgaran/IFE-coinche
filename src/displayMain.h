#ifndef DISPLAYMAIN_H
#define DISPLAYMAIN_H
#include "core.h"

/* Displays the empty frame, will be used to display the menu and the round display
*/
void displayFrame(void);
/* Clears the info box. The cursor is set to the middle of the first line
*/
void clearInfoMsg(void);

/* Displays a centered message in the info box. The cursor is left to the end of the message
*   @param messageLine1[]: the first line of the message to display
*   @param messageLine2[]: the second line of the message to display
*/
void displayInfoMsg(char messageLine1[], char messageLine2[]);

/* Resizes the command prompt window to a given number of lines and columns
*   @param nbOfLines: the number of lines that should be displayed
*   @param nbOfColumns: the number of lines that should be displayed. Microsoft docs recommands a value between 40 and 135
*/
void resizeCmdWindow(int nbOfLines, int nbOfColumns);

/* Displays the menu
*/
void displayMenu(void);

/* Executes the action selected by the user in the menu
    @param players[]: the four players that will play a game if the user selected 1. Start a game
*/
void mainMenu(Player players[]);
/* Clears the inside of the frame to switch between the different displays
*/
void clearTerminal(void);

#endif // DISPLAYMAIN_H
