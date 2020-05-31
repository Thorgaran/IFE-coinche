#ifndef USERIO_H
#define USERIO_H
#include "core.h"

Card askUserCard(Card cardArray[], int nbOfCards);

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract);

/* Displays a card at the current cursor position (the cursor comes back to that position afterwards)
*   @param card: the card to display. Only its value and color matter
*/
void displayCard(Card card);

/* Changes a card at the current cursor position (the cursor comes back to that position afterwards)
*   @param card: the card to display. Only its value and color matter
*/
void changeCardDisplay(Card card);

void displayTrick(Player* players, Color trump, Contract contract);

void updateTrickDisplay(Position playerPosition, Card playedCard, Card* playerHand, int nbOfCardsInHand);

#endif // USERIO_H