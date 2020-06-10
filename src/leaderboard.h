#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "core.h"

/* Writes a line at the current cursor position terminated by \n
*   @param *leaderboard: leaderboard file pointer
*   @param playerName[]: name of the player
*   @param wins: the player's number of wins
*/
void writeLine(FILE *leaderboard, char playerName[], int wins);

/* Seeks a player to increment its number of wins, and sort the file. If the player isn't in the file, append it at the end
*   @param playerName[]: name of the player whose number of wins should be increased
*/
void increaseWins(char playerName[]);

#endif // LEADERBOARD_H