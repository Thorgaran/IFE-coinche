#include <stdio.h>
#include <stdlib.h>
#include "core.h"

Card askUserCard(Card cardArray[], int nbOfCards) {
    Card chosenCard = {.color = SPADE, .value = SEVEN};
    return chosenCard;
}

Bool askUserContract(Card *cardArray, int nbOfCards, Contract *contract) {
    Bool hasPassed = TRUE;
    return hasPassed;
}