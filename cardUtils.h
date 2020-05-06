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
*   @param *cardArray: array containing the cards to compare
*   @param nbOfCards: how many cards are being compared
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return strongestCardPos -> the position of the strongest card in the set, where 0 is the first card of the Array
*/
int getStrongestCard(Card *cardArray, int nbOfCards, Color trump, Color roundColor);

/* Sorts the cards in an array from weakest to strongest
*   @param *cardArray: array containing the cards to sort
*   @param nbToSort: the first N cards of the array that will be sorted. Usually set to the array length to sort the whole array
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*/
void sortCards(Card *cardArray, int nbToSort, Color trump, Color roundColor);

/* Seeks a card in an array to remove it, and decreases the number of cards if it removes one
*   @param *cardArray: array containing the cards
*   @param *nbOfCards: pointer to the number of cards in cardArray
*   @param cardToRemove: the card to seek and remove in cardArray
*   @return foundCard: TRUE if the function was able to find the card (thus removing it), FALSE otherwise
*/
Bool removeCard(Card *cardArray, int *nbOfCards, Card cardToRemove);

/* In an array of cards, return only those with canPlay = TRUE, the function findValidCardsInHand must have been called before
*   @param *cardArray: array containing the cards
*   @param nbOfCards: the number of cards in cardArray
*   @param playableCards: pointer to a memory space to store the playableCards in. This array must be big enough to store all playable cards
*   @return nbOfPlayableCards: the number of cards that ended up in playableCards
*/
int getPlayableCards(Card *cardArray, int nbOfCards, Card* playableCards);

#endif