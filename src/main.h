#ifndef MAIN_H
#define MAIN_H
#include "core.h"

/**
 * \fn void mainMenu(Player players[])
 * @param players[]: the four players that will play a game if the user selected 1. Start a game
 * 
 * Executes the action selected by the user in the menu
*/
void mainMenu(Player players[]);

/** 
 * \fn void changePlayerSettings(Player players[], char quitMsg[])
 * @param players[]: array of 4 players
 * @param quitMsg[]: the text displayed as the quit option
 * 
 * Prompts the user to change player settings
*/
void changePlayerSettings(Player players[], char quitMsg[]);

/** 
 * \fn void setUp(Player players[])
 * @param players[]: array of 4 players. Each of them will be initialized
 * 
 * Sets up everything needed for the program to run, including the players
*/
void setUp(Player players[]);

/** 
 * \fn void tearDown(Player players[])
 * @param players[]: array of 4 players
 * 
 * Prepares the program for exit. Mostly frees memory
*/
void tearDown(Player players[]);

#endif // MAIN_H