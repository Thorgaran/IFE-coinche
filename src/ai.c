#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "cardUtils.h"

Card getAICardFirstAvailable(Card cardsInHand[], int nbOfCardsInHand) {
    Card chosenCard;
    int i = 0;
    while (cardsInHand[i].canPlay == FALSE) { //Seek the first playable card
        i++;
    }
    chosenCard = cardsInHand[i];
    return chosenCard;
}

Card getAICardStandard(Card cardsInHand[], int nbOfCardsInHand, Card trickCards[], int nbOfTrickCards, Color trump, Color roundColor) {
    Card chosenCard, playableCards[8];
    int bestTrickCardStrength = -1, chosenCardIndex = 0;                                    //If the AI is unable to win, it'll play its lowest card
    int nbOfPlayableCards = getPlayableCards(cardsInHand, nbOfCardsInHand, playableCards);  //Initialise both playableCards and nbOfPlayableCards
    sortCards(playableCards, nbOfPlayableCards, trump, roundColor);                         //Sort this playableCards array
    if (nbOfTrickCards > 0) {
        bestTrickCardStrength = getCardStrength(trickCards[getStrongestCard(trickCards, nbOfTrickCards, trump, roundColor)], trump, roundColor); //Find the strongest trick card's strength
    }
    if (bestTrickCardStrength < getCardStrength(playableCards[nbOfPlayableCards - 1], trump, roundColor)) { //If the AI is able to win,
        while (getCardStrength(playableCards[chosenCardIndex], trump, roundColor) < bestTrickCardStrength) {
            chosenCardIndex++;                                                                              //it does so with the lowest possible card
        }
    }
    chosenCard = playableCards[chosenCardIndex];
    return chosenCard;
}

Bool getAIContractStandard(Card cardsInHand[], int nbOfCardsInHand, Contract *contract) {
    Bool hasPassed = TRUE;
    Color strongestColor = SPADE;
    int nbOfStrongCards[] = {0, 0, 0, 0};                                               //Will contain the number of strong cards in each color, from SPADE to CLUB
    if ((*contract).coinche == NOT_COINCHED) {                                          //A player can't do another contract once one is coinched
        for (int i = 0; i < nbOfCardsInHand; i++) {                                     //Browse through each hand card
            if (getCardStrength(cardsInHand[i], ALLTRUMP, NULL_COLOR) >= 23) {          //A "strong card" is defined to be a Queen or better, in trump order (a trump queen has a strength of 23)
                nbOfStrongCards[cardsInHand[i].color - 1]++;                            //Increment the number of strong cards by one in the right color
            }
        }
        for (Color color = HEART; color <= CLUB; color++) {                             //Find the strongest color
            if (nbOfStrongCards[color - 1] > nbOfStrongCards[strongestColor - 1]) {     //If this color has more strong cards than strongestColor does,
                strongestColor = color;                                                 //then it becomes the new strongestColor
            }
        }
        if ((nbOfStrongCards[strongestColor - 1] >= 4) && ((*contract).points < 120)) { //If the AI has 4 strongs cards or more AND the current contract points are less than 120,
            hasPassed = FALSE;                                                          //it takes the contract in this color with 120 points
            (*contract).trump = strongestColor;
            (*contract).points = 120;
        }
        else if ((nbOfStrongCards[strongestColor - 1] == 3) && ((*contract).points < 80)) { //If the AI has 3 strongs cards AND the current contract points are less than 80,
            hasPassed = FALSE;                                                          //it takes the contract in this color with 80 points
            (*contract).trump = strongestColor;
            (*contract).points = 80;
        }
    }
    return hasPassed;
}