#ifndef _PLAY_H_
#define _PLAY_H_
#include "core.h"

/* Defines the "strength" of a played card in order to compare cards and find which one is stronger
*   @param card: the evaluated card
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return cardStrength -> an integer that defines the "strength" of the card, where the card with the greatest "strength" wins the trick
*/
int getCardStrength(Card card, Color trump, Color roundColor);

/* Finds the strongest card in a set
*   @param *cardArray: array containing the cards to compare
*   @param nbOfCards: how many cards are being compared
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return strongestCardPos -> the position of the strongest card in the set, where 0 is the first card of the Array
*/
int getStrongestCard(Card *cardArray, int nbOfCards, Color trump, Color roundColor);

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

/* Seeks a card in an array to remove it.
*   @param *cardArray: array containing the cards
*   @param nbOfCards: the number of cards in cardArray
*   @param cardToRemove: the card to seek and remove in cardArray
*   @return foundCard: TRUE if the function was able to find the card (thus removing it), FALSE otherwise
*/
Bool removeCard(Card *cardArray, int nbOfCards, Card cardToRemove);

//UNFINISHED FUNCTION FOR TEST PURPOSES, THE ACTUAL COMMENT WILL BE WRITTEN WHEN THE FUNCTION IS IN ITS FINAL STATE (+ askUserCard)
Card askAICard(Card *cardArray, int nbOfCards);

int playTrick(Player *players, int startingPlayer, Color trump);

void play(Player *players, int startingPlayer, Color trump);

#endif