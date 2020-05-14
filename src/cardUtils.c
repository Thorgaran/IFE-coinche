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

int getStrongestCard(Card cardArray[], int nbOfCards, Color trump, Color roundColor) {
    int greatestStrength = getCardStrength(cardArray[0], trump, roundColor);
    int cardStrength;
    int strongestCardPos = 0;

    for (int i = 1; i < nbOfCards; i++) {
        cardStrength = getCardStrength(cardArray[i], trump, roundColor); //cardStrength is needed to avoid calling getCardStrength twice
        if (cardStrength > greatestStrength) {
           greatestStrength = cardStrength;
           strongestCardPos = i;
        }
    }
    return strongestCardPos;
}

int getCardPoints(Card card, Color trump) {
    int cardPoints;
    if (trump == ALLTRUMP) {                    //If ALLTRUMP
        cardPoints = CARD_POINTS_TABLE[0][card.value - 1];
    }
    else if (trump == NOTRUMP) {                //If NOTRUMP
        cardPoints = CARD_POINTS_TABLE[1][card.value - 1];
    }
    else if (card.color == trump) {             //If the card is a trump
        cardPoints = CARD_POINTS_TABLE[2][card.value - 1];
    }
    else {                                      //If the card is not a trump
        cardPoints = CARD_POINTS_TABLE[3][card.value - 1]; 
    }
    return cardPoints;
}

int getCardArrayPoints(Card cardArray[], int nbOfCards, Color trump) {
    int totalPoints = 0;
    for (int i = 0; i < nbOfCards; i++) {
        totalPoints += getCardPoints(cardArray[i], trump);
    }
    return totalPoints;
}

Bool setCanPlay(Card cardArray[], int nbOfCards, Color conditionalColor, Color trump, int bestTrumpStrength, Bool canPlay) {
    Bool conditionMet = FALSE;
    for (int i = 0; i < nbOfCards; i++) {
        if (((conditionalColor == NULL_COLOR) || (conditionalColor == cardArray[i].color)) &&
        ((cardArray[i].color != trump) || (getCardStrength(cardArray[i], trump, NULL_COLOR) > bestTrumpStrength))) {
            //If the card is the right color (or if the condition is bypassed with NULL_COLOR), AND if the card isn't a trump weaker than the best one on the table
            cardArray[i].canPlay = canPlay;
            conditionMet = TRUE;
        }
    }
    return conditionMet;
}

void sortCards(Card cardArray[], int nbToSort, Color trump, Color roundColor) { //Bubble sort algorithm
    Card previousCard;
    int newNbToSort;
    while (nbToSort > 1) { //While there is more than a single card left to sort
        newNbToSort = 0;
        for (int i = 1; i < nbToSort; i++) {
            previousCard = cardArray[i - 1]; //Variable needed for the swap
            if (getCardStrength(previousCard, trump, roundColor) > getCardStrength(cardArray[i], trump, roundColor)) {
            //If the previous card is stonger than the current card
                cardArray[i - 1] = cardArray[i]; //Swap cards
                cardArray[i] = previousCard;
                newNbToSort = i; //On the next array pass, no need to go past the last card swapped in this pass
            }
        }
        nbToSort = newNbToSort; //nbToSort cannot be updated directly in the for loop to avoid breaking the exit condition
    }
}

Bool removeCard(Card cardArray[], int *nbOfCards, Card cardToRemove) {
    Bool foundCard = FALSE;
    for (int i = 0; i < (*nbOfCards); i++) {
        if (foundCard == TRUE) { //The card has been found
            cardArray[i-1] = cardArray[i]; //Move this card to replace the previous one
        }
        else if ((cardArray[i].value == cardToRemove.value) && (cardArray[i].color == cardToRemove.color)) { //Is this the card we're looking for?
            foundCard = TRUE; //If it is, then stop looking for it and start moving cards
        }
    }
    if (foundCard == TRUE) { //The number of cards shouldn't be decreased if no card was removed
        (*nbOfCards)--; //Decrease the number of cards in the array
    }
    return foundCard;
}

int getPlayableCards(Card cardArray[], int nbOfCards, Card playableCards[]) {
    int nbOfPlayableCards = 0;
    for (int i = 0; i < nbOfCards; i++) {
        if (cardArray[i].canPlay == TRUE) {                     //If the card can be played,
            playableCards[nbOfPlayableCards] = cardArray[i];    //add it to the playableCards array,
            nbOfPlayableCards++;                                //and increment the number of playable cards
        }
    }
    return nbOfPlayableCards;
}

void createDeck(Card cardDeck[]) {
    int cardNb = 0;
    for(int color = SPADE; color <= CLUB; color++) {
        for(int value = SEVEN; value <= ACE; value++) {
            cardDeck[cardNb].color = color;
            cardDeck[cardNb].value = value;
            cardNb ++; //CardNb is needed to keep track of where the program needs to add the following card
        }
    }
}

void cardsDistribution(Player players[]) {
    Card cardDeck[32];
    int randomCardNb;
    int nbOfRemainingCards = 32;
    createDeck(cardDeck); //Prepare the full deck that will be dealed
    for (int cardIndex = 0; cardIndex < 8; cardIndex++) {
        for (Position player = SOUTH; player <= EAST; player++) {
            randomCardNb = rand()%(nbOfRemainingCards);                         //Choose a card among the remaining ones
            players[player].cards[cardIndex] = cardDeck[randomCardNb];          //Give that card to the player,
            removeCard(cardDeck, &nbOfRemainingCards, cardDeck[randomCardNb]);  //and remove it from the deck
        } 
    }
}