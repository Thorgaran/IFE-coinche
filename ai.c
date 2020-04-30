#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "cardUtils.h"

Card getAICardFirstAvailable(Card *cardArray, int nbOfCards) { //TEMPORARY FOR TEST PUROPOSES, WILL NEED AN UPDATE LATER
    Card chosenCard;
    int i = 0;
    while ((cardArray[i].canPlay == FALSE) && (i < nbOfCards)) {
        i++;
    }
    if (i == nbOfCards) {
        printf("ERROR!!! NO AVAILABLE CARD\n");
        chosenCard = cardArray[i];
    }
    else {
        chosenCard = cardArray[i];
    }
    return chosenCard;
}

Card getAICardStandard(Card *cardArray, int nbOfCards) {
    Card chosenCard = {.color = SPADE, .value = SEVEN};

    return chosenCard;
}