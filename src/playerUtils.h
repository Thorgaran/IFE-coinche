#ifndef PLAYERUTILS_H
#define PLAYERUTILS_H
#include "core.h"

/** 
 * \fn Card getPlayerCard(Player *player, Card trickCards[], int nbOfTrickCards, Color trump, Color roundColor)
 * @param *player: pointer to the player who has to choose a card. Note: the "canPlay" flag for the player cards has to be set already
 * @param trickCards[]: the cards already played by the previous players. Only the first N cards matter, where N is nbOfTrickCards
 * @param nbOfTrickCards: the number of cards played by the previous players. Can be 0
 * @param trump: the current trump
 * @param roundColor: the color of the first played card in the round
 * @return chosenCard: the chosen card
 * 
 * Get the player to choose a card among the ones that can be played, depending on the player type (User/AI)
*/
Card getPlayerCard(Player *player, Card trickCards[], int nbOfTrickCards, Color trump, Color roundColor);

/** 
 * \fn Bool getPlayerContract(Player player, Contract *contract)
 * @param player: the player who has to make a decision
 * @param *contract: pointer to the contract being debated. Will be edited if the player decides to make a contract
 * @return hasPassed: TRUE if the player has decided to pass, FALSE if the player decided to make a contract
 * 
 * Get the player to decide whether or not to make a contract, depending on the player type (User/AI)
*/
Bool getPlayerContract(Player player, Contract *contract);

/** 
 * \fn void cardsDistribution(Player players[])
 * @param players[]: array of 4 players
 * 
 * Function that randomly deals 8 of the 32 cards to each player at the beginning of bidding
*/
void cardsDistribution(Player players[]);

/** 
 * \fn int getTeamRoundPoints(Player players[], Position player)
 * @param players[]: array of 4 players
 * @param player: position of a player in the team of interest
 * @return roundPoints: the total round points of the team
 * 
 * Get a team's total trick points from the previous round
*/
int getTeamRoundPoints(Player players[], Position player);

/** 
 * \fn void increaseTeamTotalScore(Player players[], Position player, int roundScore)
 * @param players[]: array of 4 players
 * @param player: position of a player in the team of interest
 * @param roundScore: how much the team's total score should be increased by
 * 
 * Increase a team's total score 
*/
void increaseTeamTotalScore(Player players[], Position player, int roundScore);

#endif // PLAYERUTILS_H
