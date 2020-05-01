#ifndef _AI_H_
#define _AI_H_
#include "core.h"

/* Returns the first playable card in the AI's hand
*   @param *cardsInHand: pointer to the first address of a player's hand 
*   @param nbOfCardsInHand: the number of cards in hand
*   @return chosenCard: the chosen card
*/
Card getAICardFirstAvailable(Card *cardsInHand, int nbOfCardsInHand);

/* If the AI is able to win the trick with one of its cards, it does so by playing the lowest possible card
*  If the AI is unable to win, it plays its lowest card
*   @param *cardsInHand: pointer to the first address of a player's hand 
*   @param nbOfCardsInHand: the number of cards in hand
*   @param *trickCards: the cards already played by the previous players. Only the first N cards matter, where N is nbOfTrickCards
*   @param nbOfTrickCards: the number of cards played by the previous players. Can be 0
*   @return playableCards[chosenCardIndex]: the chosen card
*/
Card getAICardStandard(Card *cardsInHand, int nbOfCardsInHand, Card *trickCards, int nbOfTrickCards, Color trump, Color roundColor);

#endif