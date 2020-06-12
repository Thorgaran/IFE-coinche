#ifndef MAIN_H
#define MAIN_H
#include "core.h"

/* Executes the action selected by the user in the menu
    @param players[]: the four players that will play a game if the user selected 1. Start a game
*/
void mainMenu(Player players[]);

/* Sets up everything needed for the program to run, including the players
*   @param players[]: array of 4 players. Each of them will be initialized
*/
void setUp(Player players[]);

/* Prepares the program for exit. Mostly frees memory
*   @param players[]: array of 4 players
*/
void tearDown(Player players[]);

#endif // MAIN_H