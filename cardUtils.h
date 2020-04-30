#ifndef _CARDUTILS_H_
#define _CARDUTILS_H_
#include "core.h"

/* Defines the "strength" of a played card in order to compare cards and find which one is stronger
*   @param card: the evaluated card
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return cardStrength -> an integer that defines the "strength" of the card, where the card with the greatest "strength" wins the trick
*/
int getCardStrength(Card card, Color trump, Color roundColor);

/* Finds the strongest card in a set
*   @param mode: set to STRONGEST or WEAKEST depending on the card you're looking for
*   @param *cardArray: array containing the cards to compare
*   @param nbOfCards: how many cards are being compared
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return strongestCardPos -> the position of the strongest card in the set, where 0 is the first card of the Array
*/
int getStrongestOrWeakestCard(int mode, Card *cardArray, int nbOfCards, Color trump, Color roundColor);

/* Seeks a card in an array to remove it
*   @param *cardArray: array containing the cards
*   @param nbOfCards: the number of cards in cardArray
*   @param cardToRemove: the card to seek and remove in cardArray
*   @return foundCard: TRUE if the function was able to find the card (thus removing it), FALSE otherwise
*/
Bool removeCard(Card *cardArray, int nbOfCards, Card cardToRemove);

#endif