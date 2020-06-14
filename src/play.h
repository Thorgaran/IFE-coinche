#ifndef PLAY_H
#define PLAY_H
#include "core.h"

/** 
 * \fn Bool bidAttempt(Player players[], Position startingPlayer, Contract *contract)
 * @param players[]: array of 4 players
 * @param startingPlayer: position of the starting player
 * @param *contract: pointer to the contract being debated. Will be edited someone decides to make a contract
 * @return everyonePassed: FALSE if a contract was made, TRUE otherwise
 * 
 * Play a bid attempt: either a contract is made or everyone passed
*/
Bool bidAttempt(Player players[], Position startingPlayer, Contract *contract);

/**
 * \fn Contract bidUntilContract(Player players[], Position startingPlayer)
 * @param players[]: array of 4 players
 * @param startingPlayer: position of the starting player
 * @return contract: the contract that was made
 * 
 *  Deal cards and play bid attempts until a contract is made
*/
Contract bidUntilContract(Player players[], Position startingPlayer);

/**
 * \fn Position playTrick(Player players[], Position startingPlayer, Color trump)
 * @param players[]: array of 4 players
 * @param startingPlayer: position of the starting player
 * @param trump: the current trump
 * @return trickWinner: position of the winner of the trick
 * 
 *  Plays a single trick : each player plays a card, then the player with the strongest card wins the trick and gets points
*/
Position playTrick(Player players[], Position startingPlayer, Color trump);

/** 
 * \fn void playRound(Player players[], Position startingPlayer, Color trump)
 * @param players[]: array of 4 players
 * @param startingPlayer: position of the starting player
 * @param trump: the current trump
 * 
 * Plays a full 8-trick round, counting points
*/
void playRound(Player players[], Position startingPlayer, Color trump);

/** 
 * \fn void awardTeamPoints(Player players[], Contract contract)
 * @param players[]: array of 4 players
 * @param contract: the contract that was previously made
 * 
 * Do the aftermaths of a round: check whether or not the contract issuer's team fulfilled the contract, and award points accordingly
*/
void awardTeamPoints(Player players[], Contract contract);

/** 
 * \fn int playGame(Player players[])
 * @param players[]: array of 4 players
 * @return currentRound: the number of rounds played
 * 
 * Plays a full game until a team wins (it reaches 701 points)
*/
int playGame(Player players[]);

/** 
 * \fn float playAIGames(Player players[], int nbOfGames, int nbOfGamesWon[])
 * @param players[]: array of 4 players
 * @param nbOfGames: the number of games to be played
 * @param nbOfGamesWon[]: empty array of length 2. The number of game won by each team will be written in it
 * @return averageGameLength: average number of rounds played for each game
 * 
 * Plays a given number of AI games and returns some stats
*/
float playAIGames(Player players[], int nbOfGames, int nbOfGamesWon[]);

#endif // PLAY_H