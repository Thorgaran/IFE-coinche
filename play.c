#include <stdio.h>
#include <stdlib.h>
#include "core.h"

int getCardStrength(cardType card, colorType trump, colorType roundColor) {
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

int getStrongestCard(cardType *cardArray, int numberOfCards, colorType trump, colorType roundColor) {
    int greatestStrength = getCardStrength(cardArray[0], trump, roundColor);
    int cardStrength;
    int strongestCardPos = 0;

    for (int i = 1; i < numberOfCards; i++) {
        cardStrength = getCardStrength(cardArray[i], trump, roundColor); //cardStrength is needed to avoid calling getCardStrength twice
        if (cardStrength > greatestStrength) {
           greatestStrength = cardStrength;
           strongestCardPos = i;
        }
    }
    return strongestCardPos;
}

int getCardPoints(cardType card, colorType trump) {
    int cardPoints;
    if (trump == ALLTRUMP) {                    //If ALLTRUMP
        cardPoints = CARD_POINTS_TABLE[0][card.value];
    }
    else if (trump == NOTRUMP) {                //If NOTRUMP
        cardPoints = CARD_POINTS_TABLE[1][card.value];
    }
    else if (card.color == trump) {             //If the card is a trump
        cardPoints = CARD_POINTS_TABLE[2][card.value];
    }
    else {                                      //If the card is not a trump
        cardPoints = CARD_POINTS_TABLE[3][card.value]; 
    }
    return cardPoints;
}

int getCardArrayPoints(cardType *cardArray, int numberOfCards, colorType trump) {
    int totalPoints = 0;
    for (int i = 0; i < numberOfCards; i++) {
        totalPoints += getCardPoints(cardArray[i], trump);
    }
    return totalPoints;
}