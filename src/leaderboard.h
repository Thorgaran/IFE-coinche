#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "core.h"

/** 
 * \fn void writeLine(FILE *leaderboard, char playerName[], int wins)
 * @param *leaderboard: leaderboard file pointer
 * @param playerName[]: name of the player
 * @param wins: the player's number of wins
 * 
 * Writes a line at the current cursor position terminated by \n
*/
void writeLine(FILE *leaderboard, char playerName[], int wins);

/** 
 * \fn void increaseWins(char playerName[])
 * @param playerName[]: name of the player whose number of wins should be increased
 * 
 * Seeks a player to increment its number of wins, and sort the file. If the player isn't in the file, append it at the end
*/
void increaseWins(char playerName[]);

/** 
 * \fn int getTopTen(char names[][MAX_PLAYER_NAME_LENGTH+1], int wins[])
 * @param names[][MAX_PLAYER_NAME_LENGTH+1]: empty two-dimensional array of chars, will be filled with the top ten player names
 * @param wins[]: empty array of integers, will be filled with the top ten player wins
 * @return nbOfPlayers: the number of players found in the file, from 0 to 10
 * 
 * Retrieves the top ten players in the leaderboard file
*/
int getTopTen(char names[][MAX_PLAYER_NAME_LENGTH+1], int wins[]);

#endif // LEADERBOARD_H