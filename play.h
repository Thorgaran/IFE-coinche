#ifndef _PLAY_H_
#define _PLAY_H_
#include "core.h"

/* Finds the point value of a card depending on the current trump
*   @param card: the evaluated card
*   @param trump: the current trump
*   @return cardPoints -> the point value of the card
*/
int getCardPoints(Card card, Color trump);

/* Computes the total point value of an Array of cards
*   @param *cardArray: array containing the cards
*   @param nbOfCards: how many cards are in cardArray
*   @param trump: the current trump
*   @return totalPoints -> the sum of the point value of each card in cardArray
*/
int getCardArrayPoints(Card *cardArray, int nbOfCards, Color trump);

/* Sets the canPlay property of each card if it meets a color criteria and if it's not a weaker trump than the current best one
*   @param *cardArray: array containing the cards
*   @param nbOfCards: how many cards are in cardArray
*   @param conditionalColor: the canPlay property of each card will be set if its color is conditionalColor. Set to NULL_COLOR to bypass the condition
*   @param trump: the current trump
*   @param bestTrumpStrength: the current best trump's Strength. A card will not be set if it's a trump weaker than this. Set to 0 to bypass the condition
*   @param canPlay: the Bool value canPlay property should be set to
*   @return conditionMet -> FALSE if no canPlay property was changed, TRUE otherwise
*/
Bool setCanPlay(Card *cardArray, int nbOfCards, Color conditionalColor, Color trump, int bestTrumpStrength, Bool canPlay);

/* Sets the canPlay property of each card in an Array to find which ones can be played depending on the cards currently on the table
*   @param *cardsInHand: the first N cards of this Array will be evaluated to find the valid ones to play according to the coinche rules
*   @param nbOfCardsInHand: the number of cards this function should look at to see which ones are valid
*   @param *trickCards: the cards already played by the previous players. Only the first N cards matter, where N is nbOfTrickCards
*   @param nbOfTrickCards: the number of cards played by the previous players. Can be 0
*   @param trump: the current trump
*/
void findValidCardsInHand(Card *cardsInHand, int nbOfCardsInHand, Card *trickCards, int nbOfTrickCards, Color trump);

/* Get the player to choose a card among the ones that can be played, depending on the player type (User/AI)
*   @param *player: pointer to the player who has to choose a card. Note: the "canPlay" flag for the player cards has to be set already
*   @param *trickCards: the cards already played by the previous players. Only the first N cards matter, where N is nbOfTrickCards
*   @param nbOfTrickCards: the number of cards played by the previous players. Can be 0
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return chosenCard: the chosen card
*/
Card getPlayerCard(Player *player, Card *trickCards, int nbOfTrickCards, Color trump, Color roundColor);

/* Plays a single trick : each player plays a card, then the player with the strongest card wins the trick and gets points
*   @param *players: pointer to an array of 4 players
*   @param startingPlayer: number from 0 to 3, representing the starting player
*   @param trump: the current trump
*   @return trickWinner: number from 0 to 3, representing the winner of the trick
*/
int playTrick(Player *players, Position startingPlayer, Color trump);

/* Plays a full 8-trick game, counting points
    @param *players: pointer to an array of 4 players
    @param startingPlayer: number from 0 to 3, representing the starting player
    @param trump: the current trump
*/
void play(Player *players, Position startingPlayer, Color trump);

#endif