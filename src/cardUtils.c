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
        if (cardArray[i].canPlay == TRUE) {
            playableCards[nbOfPlayableCards] = cardArray[i];
            nbOfPlayableCards++;
        }
    }
    return nbOfPlayableCards;
}

void CardsDistribution (void){
    Card cardDeck[32];
    int cardNb = 0;
    //int nbOfDistributedCards = 0;

    for(int i = 1; i < 5; i++){
        for(int j = 1; j < 9; j++){
            cardDeck[cardNb].color = i;
            cardDeck[cardNb].value = j;
            cardNb ++;
        }
    }
    for (int i = 0; i < 32; i++)
    {
        printf("%d %d\n",cardDeck[i].color,cardDeck[i].value);
    }

}