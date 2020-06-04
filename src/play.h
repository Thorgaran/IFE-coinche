#ifndef PLAY_H
#define PLAY_H
#include "core.h"

/* Play a bid attempt: either a contract is made or everyone passed
*   @param players[]: array of 4 players
*   @param startingPlayer: position of the starting player
*   @param *contract: pointer to the contract being debated. Will be edited someone decides to make a contract
*   @return everyonePassed: FALSE if a contract was made, TRUE otherwise
*/
Bool bidAttempt(Player players[], Position startingPlayer, Contract *contract);

/* Deal cards and play bid attempts until a contract is made
*   @param players[]: array of 4 players
*   @param startingPlayer: position of the starting player
*   @return contract: the contract that was made
*/
Contract bidUntilContract(Player players[], Position startingPlayer);

/* Plays a single trick : each player plays a card, then the player with the strongest card wins the trick and gets points
*   @param players[]: array of 4 players
*   @param startingPlayer: position of the starting player
*   @param trump: the current trump
*   @return trickWinner: position of the winner of the trick
*/
Position playTrick(Player players[], Position startingPlayer, Color trump);

/* Plays a full 8-trick round, counting points
*   @param players[]: array of 4 players
*   @param startingPlayer: position of the starting player
*   @param trump: the current trump
*/
void playRound(Player players[], Position startingPlayer, Color trump);

/* Do the aftermaths of a round: check whether or not the contract issuer's team fulfilled the contract, and award points accordingly
*   @param players[]: array of 4 players
*   @param contract: the contract that was previously made
*/
void awardTeamPoints(Player players[], Contract contract);

/* Plays a full game until a team wins (it reaches 701 points)
*   @param players[]: array of 4 players
*   @return currentRound: the number of rounds played
*/
int playGame(Player players[]);

/* Plays a given number of AI games and returns some stats
*   @param players[]: array of 4 players
*   @param nbOfGames: the number of games to be played
*   @param nbOfGamesWon[]: empty array of length 2. The number of game won by each team will be written in it
*   @return averageGameLength: average number of rounds played for each game
*/
float playAIGames(Player players[], int nbOfGames, int nbOfGamesWon[]);

#endif // PLAY_H