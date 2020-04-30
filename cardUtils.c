#include <stdio.h>
#include <stdlib.h>
#include "core.h"

int getCardStrength(Card card, Color trump, Color roundColor) {
    int cardStrength = card.value;

    if (card.color == roundColor) {
        cardStrength += 10;                             // If the card has the right color, its strength increases
    }

    if ((trump == card.color) || (trump == ALLTRUMP)) {
        cardStrength += 18;                             // If the card is a trump, its strength increases
        if ((card.value == NINE) || (card.value == JACK)) {
            cardStrength += 6;                          // If the card is a trump and a 9 or a jack, its strength increases again according to the belotte rules
        }
    }
    return cardStrength;
}

int getStrongestOrWeakestCard(int mode, Card *cardArray, int nbOfCards, Color trump, Color roundColor) {
    int greatestStrength = getCardStrength(cardArray[0], trump, roundColor);
    int cardStrength;
    int strongestCardPos = 0;

    for (int i = 1; i < nbOfCards; i++) {
        cardStrength = getCardStrength(cardArray[i], trump, roundColor); //cardStrength is needed to avoid calling getCardStrength twice
        if (cardStrength > (mode * greatestStrength)) {
           greatestStrength = cardStrength;
           strongestCardPos = i;
        }
    }
    return strongestCardPos;
}

Bool removeCard(Card *cardArray, int nbOfCards, Card cardToRemove) {
    Bool foundCard = FALSE;
    for (int i = 0; i < nbOfCards; i++) {
        if (foundCard == TRUE) {
            cardArray[i-1] = cardArray[i];
        }
        else if ((cardArray[i].value == cardToRemove.value) && (cardArray[i].color == cardToRemove.color)) {
            foundCard = TRUE;
        }
    }
    if (foundCard == TRUE) {
        cardArray[nbOfCards-1].value = NULL_VALUE;
        cardArray[nbOfCards-1].color = NULL_COLOR;
    }
    return foundCard;
}