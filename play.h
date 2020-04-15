#ifndef _PLAY_H_
#define _PLAY_H_
#include "core.h"

/* Defines the "strength" of a played card in order to compare cards and find which one is stronger
*   @param card: the evaluated card
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return cardStrength -> an integer that defines the "strength" of the card, where the card with the greatest "strength" wins the trick
*/
int getCardStrength(cardType card, colorType trump, colorType roundColor);

/* Finds the strongest card in a set
*   @param *cardArray: array containing the cards to compare
*   @param numberOfCards: how many cards are being compared
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return strongestCardPos -> the position of the strongest card in the set, where 0 is the first card of the Array
*/
int getStrongestCard(cardType *cardArray, int numberOfCards, colorType trump, colorType roundColor);

/* Finds the point value of a card depending on the current trump
*   @param card: the evaluated card
*   @param trump: the current trump
*   @return cardPoints -> the point value of the card
*/
int getCardPoints(cardType card, colorType trump);

/* Computes the total point value of an Array of cards
*   @param *cardArray: array containing the cards
*   @param numberOfCards: how many cards are in cardArray
*   @param trump: the current trump
*   @return totalPoints -> the sum of the point value of each card in cardArray
*/
int getCardArrayPoints(cardType *cardArray, int numberOfCards, colorType trump);

#endif