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

int getStrongestCard(cardType *cardArray, int nbOfCards, colorType trump, colorType roundColor) {
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

int getCardPoints(cardType card, colorType trump) {
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

int getCardArrayPoints(cardType *cardArray, int nbOfCards, colorType trump) {
    int totalPoints = 0;
    for (int i = 0; i < nbOfCards; i++) {
        totalPoints += getCardPoints(cardArray[i], trump);
    }
    return totalPoints;
}

bool setCanPlay(cardType *cardArray, int nbOfCards, colorType conditionalColor, cardType bestTrump, bool canPlay) {
    bool conditionMet = FALSE;
    for (int i = 0; i < nbOfCards; i++) {
        if (((conditionalColor == NULL_COLOR) || (conditionalColor == cardArray[i].color)) && ((cardArray[i].color != bestTrump.color) || (cardArray[i].value > bestTrump.value))) {
            //If the card is the right color (or if the condition is bypassed with NULL_COLOR), AND if the card isn't a trump weaker than the best one on the table
            cardArray[i].canPlay = canPlay;
            conditionMet = TRUE;
        }
    }
    return conditionMet;
}

void findValidCardsInHand(cardType *cardsInHand, int nbOfCardsInHand, cardType *trickCards, int nbOfTrickCards, colorType trump) {
    bool canFollow;
    cardType bestTrump = {.color = trump, .value = NULL_VALUE};                                                     //The best current trump, will be used later
    cardType nullCard = {.color = NULL_COLOR, .value = NULL_VALUE};                                                 //nullCard is used to bypass any trump condition in SetCanPlay
    setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, nullCard, FALSE);                                          //Each card is initialised to canPlay = FALSE

    if (nbOfTrickCards == 0) {                                                                                      //The first player of a trick
        setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, nullCard, TRUE);                                       //can play any card.
    }
    else {
        if (trump == ALLTRUMP) {
            trump = trickCards[0].color;
            bestTrump.color = trump;
        }
        for (int i = 0; i < nbOfTrickCards; i++) {                                                                  //Find the best trump in the current trick cards
            if (trickCards[i].color == trump) {
                if ((trickCards[i].value == NINE) || (trickCards[i].value == JACK)) {
                    trickCards[i].value += 6;                                                                       //In trickCards, change temporarily the value of NINE and JACK trump cards to TRUMP_NINE and TRUMP_JACK
                }
                if (trickCards[i].value > bestTrump.value) {
                    bestTrump.value = trickCards[i].value;
                }
            }
        }
        for (int i = 0; i < nbOfCardsInHand; i++) {
            if ((cardsInHand[i].color == trump) && ((cardsInHand[i].value == NINE) || (cardsInHand[i].value == JACK))) {
                cardsInHand[i].value += 6;                                                                          //In cardsInHand, change temporarily the value of NINE and JACK trump cards to TRUMP_NINE and TRUMP_JACK
            }
        }
        canFollow = setCanPlay(cardsInHand, nbOfCardsInHand, trickCards[0].color, bestTrump, TRUE);                 //A player must follow in the right color. If that color is a trump, the player has to play a stronger card. 
        if ((trickCards[0].color == trump) && (canFollow == FALSE)) {                                               //If the trick was started with a trump AND playing a higher trump than the current best one is impossible,
            canFollow = setCanPlay(cardsInHand, nbOfCardsInHand, trickCards[0].color, nullCard, TRUE);              //the player has to follow with a lower trump.
        }
        if (canFollow == FALSE) {                                                                                   //If playing in the right color is impossible:
            if (getStrongestCard(trickCards, nbOfTrickCards, trump, trickCards[0].color) == (nbOfTrickCards - 2)) { //If a player's partner is the current trick winner,
                setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, nullCard, TRUE);                               //any card can be played.
            }
            else {
                canFollow = setCanPlay(cardsInHand, nbOfCardsInHand, trump, bestTrump, TRUE);                       //A player must play a stronger trump card than the current best one if its partner isn't winning.
                if (canFollow == FALSE) {                                                                           //If all of the above are impossible,
                    setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, nullCard, TRUE);                           //the player can play any card.
                }
            }
        }        
        for (int i = 0; i < nbOfTrickCards; i++) {
            if ((trickCards[i].value == TRUMP_NINE) || (trickCards[i].value == TRUMP_JACK)) {
                trickCards[i].value -= 6;                                                                           //In trickCards, reset any TRUMP_NINE and TRUMP_JACK to NINE and JACK
            }
        }
        for (int i = 0; i < nbOfCardsInHand; i++) {
            if ((cardsInHand[i].value == TRUMP_NINE) || (cardsInHand[i].value == TRUMP_JACK)) {
                cardsInHand[i].value -= 6;                                                                          //In cardsInHand, reset any TRUMP_NINE and TRUMP_JACK to NINE and JACK
            }
        }
    }    
}

bool removeCard(cardType *cardArray, int nbOfCards, cardType cardToRemove) {
    bool foundCard = FALSE;
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

cardType askAICard(cardType *cardArray, int nbOfCards) { //TEMPORARY FOR TEST PUROPOSES, WILL NEED AN UPDATE LATER
    cardType chosenCard;
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
    removeCard(cardArray, nbOfCards, chosenCard);
    return chosenCard;
}

int playTrick(Player *players, int startingPlayer, colorType trump) {
    cardType trickCards[4];
    int trickWinner;
    for (int i = 0; i < 4; i++) {
        findValidCardsInHand(players[(i+startingPlayer)%4].cards, players[(i+startingPlayer)%4].nbOfCards, trickCards, i, trump);
        for (int j = 0; j < players[(i+startingPlayer)%4].nbOfCards; j++) { //TEMP DEBUG FEEDBACK
            printf("%d ", players[(i+startingPlayer)%4].cards[j].canPlay);  //TEMP DEBUG FEEDBACK
        }                                                                   //TEMP DEBUG FEEDBACK
        printf("\n");                                                       //TEMP DEBUG FEEDBACK

        if (players[(i + startingPlayer) % 4].isUser == TRUE) {
            trickCards[i] = askAICard(players[(i+startingPlayer)%4].cards, players[(i+startingPlayer)%4].nbOfCards); //change to AskUserCard later
        }
        else {
            trickCards[i] = askAICard(players[(i+startingPlayer)%4].cards, players[(i+startingPlayer)%4].nbOfCards);
        }
        players[(i+startingPlayer)%4].nbOfCards -= 1;
    }
    trickWinner = (getStrongestCard(trickCards, 4, trump, trickCards[0].color) + startingPlayer) % 4;
    //getStrongestCard returns a relative value while trickWinner needs an absolute one, hence the conversion with startingPlayer and a modulo
    players[trickWinner].score += getCardArrayPoints(trickCards, 4, trump);
    printf("Player %d wins the trick and gets %d points, for a total of %d!\n", trickWinner, getCardArrayPoints(trickCards, 4, trump), players[trickWinner].score); //TEMP DEBUG FEEDBACK
    return trickWinner;
}

void play(Player *players, int startingPlayer, colorType trump) { //Trump, player's hands, return each team's points ; playerHands[0] is the user's hand?
    for (int i = 0; i < 8; i++) {
        startingPlayer = playTrick(players, startingPlayer, trump);
    }
    players[startingPlayer].score += 10; //10 bonus points for the last trick's winner
}