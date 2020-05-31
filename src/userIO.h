#ifndef USERIO_H
#define USERIO_H
#include "core.h"

Card askUserCard(Card cardArray[], int nbOfCards);

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract);

void displayTrick(Player* players, Color trump, Contract contract);

void updateTrickDisplay(Position playerPosition, Card playedCard, Card* playerHand, int nbOfCardsInHand);

#endif // USERIO_H