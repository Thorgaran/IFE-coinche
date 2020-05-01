#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "cardUtils.h"

Card getAICardFirstAvailable(Card *cardsInHand, int nbOfCardsInHand) {
    Card chosenCard;
    int i = 0;
    while ((cardsInHand[i].canPlay == FALSE) && (i < nbOfCardsInHand)) {
        i++;
    }
    if (i == nbOfCardsInHand) {
        printf("ERROR!!! NO AVAILABLE CARD\n");
        chosenCard = cardsInHand[i];
    }
    else {
        chosenCard = cardsInHand[i];
    }
    return chosenCard;
}

Card getAICardStandard(Card *cardsInHand, int nbOfCardsInHand, Card *trickCards, int nbOfTrickCards, Color trump, Color roundColor) {
    Card playableCards[8];
    int bestTrickCardStrength, chosenCardIndex = 0;                                         //If the AI is unable to win, it'll play its lowest card
    int nbOfPlayableCards = getPlayableCards(cardsInHand, nbOfCardsInHand, playableCards);  //Initialise both playableCards and nbOfPlayableCards
    sortCards(playableCards, nbOfPlayableCards, trump, roundColor);                         //Sort this playableCards array
    bestTrickCardStrength = getCardStrength(trickCards[getStrongestCard(trickCards, nbOfTrickCards, trump, roundColor)], trump, roundColor); //Find the strongest trick card
    if (bestTrickCardStrength < getCardStrength(playableCards[nbOfPlayableCards - 1], trump, roundColor)) { //If the AI is able to win,
        while (getCardStrength(playableCards[chosenCardIndex], trump, roundColor) < bestTrickCardStrength) {
            chosenCardIndex++;                                                                              //it does so with the lowest possible card
        }
    }
    return playableCards[chosenCardIndex];
}