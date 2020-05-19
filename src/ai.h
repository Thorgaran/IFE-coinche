#ifndef AI_H
#define AI_H
#include "core.h"

/* Returns the first playable card in the AI's hand
*   @param cardsInHand[]: array containing the cards in the AI's hand 
*   @param nbOfCardsInHand: the number of cards in the array cardsInHand
*   @return chosenCard: the chosen card
*/
Card getAICardFirstAvailable(Card cardsInHand[], int nbOfCardsInHand);

/* If the AI is able to win the trick with one of its cards, it does so by playing the lowest possible card
*  If the AI is unable to win, it plays its lowest card
*   @param cardsInHand[]: array containing the cards in the AI's hand
*   @param nbOfCardsInHand: the number of cards in in the array cardsInHand
*   @param trickCards[]: array containing the cards already played by the previous players. Only the first N cards matter, where N is nbOfTrickCards
*   @param nbOfTrickCards: the number of cards played by the previous players. Can be 0
*   @param trump: the current trump
*   @param roundColor: the color of the first card played of that trick
*   @return chosenCard: the chosen card
*/
Card getAICardStandard(Card cardsInHand[], int nbOfCardsInHand, Card trickCards[], int nbOfTrickCards, Color trump, Color roundColor);

/* This AI always makes an 80 points contract in its first card's color if it can
*   @param cardsInHand[]: array containing the cards in the AI's hand
*   @param *contract: pointer to the contract being debated. Will be edited if the AI decides to make a contract
*   @return hasPassed: TRUE if the AI has decided to pass, FALSE if it decided to make a contract
*/
Bool getAIContractAlwaysEighty(Card cardsInHand[], Contract *contract);

/* If the AI has 4 strong cards or more in a given color, it makes a 120 points contract. If it has 3 strong cards, it makes an 80 points one
*   @param cardsInHand[]: array containing the cards in the AI's hand
*   @param nbOfCardsInHand: the number of cards in hand
*   @param *contract: pointer to the contract being debated. Will be edited if the AI decides to make a contract
*   @return hasPassed: TRUE if the AI has decided to pass, FALSE if it decided to make a contract
*/
Bool getAIContractStandard(Card cardsInHand[], int nbOfCardsInHand, Contract *contract);

#endif // AI_H