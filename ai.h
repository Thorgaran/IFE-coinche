#ifndef _AI_H_
#define _AI_H_
#include "core.h"

/* Returns the first playable card in the AI's hand
*   @param *cardArray: pointer to the first address of a player's hand 
*   @param nbOfCards: the number of cards in hand
*   @return chosenCard: the chosen card
*/
Card getAICardFirstAvailable(Card *cardArray, int nbOfCards);

/* If the AI is able to win the trick with one of its cards, it does so by playing the lowest possible card
*  If the AI is unable to win, it plays its lowest card
*   @param *cardArray: pointer to the first address of a player's hand 
*   @param nbOfCards: the number of cards in hand
*   @return chosenCard: the chosen card
*/
Card getAICardStandard(Card *cardArray, int nbOfCards);

#endif