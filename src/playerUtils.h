#ifndef PLAYERUTILS_H
#define PLAYERUTILS_H
#include "core.h"

/* Get the player to choose a card among the ones that can be played, depending on the player type (User/AI)
*   @param *player: pointer to the player who has to choose a card. Note: the "canPlay" flag for the player cards has to be set already
*   @param trickCards[]: the cards already played by the previous players. Only the first N cards matter, where N is nbOfTrickCards
*   @param nbOfTrickCards: the number of cards played by the previous players. Can be 0
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return chosenCard: the chosen card
*/
Card getPlayerCard(Player *player, Card trickCards[], int nbOfTrickCards, Color trump, Color roundColor);

/* Get the player to decide whether or not to make a contract, depending on the player type (User/AI)
*   @param player: the player who has to make a decision
*   @param *contract: pointer to the contract being debated. Will be edited if the player decides to make a contract
*   @return hasPassed: TRUE if the player has decided to pass, FALSE if the player decided to make a contract
*/
Bool getPlayerContract(Player player, Contract *contract);

/* Get a team's total trick points from the previous round
*   @param players[]: array of 4 players
*   @param player: position of a player in the team of interest
*   @return roundPoints: the total round points of the team
*/
int getTeamRoundPoints(Player players[], Position player);

/* Increase a team's total score 
*   @param players[]: array of 4 players
*   @param player: position of a player in the team of interest
*   @param roundScore: how much the team's total score should be increased by
*/
void increaseTeamTotalScore(Player players[], Position player, int roundScore);

#endif // PLAYERUTILS_H
