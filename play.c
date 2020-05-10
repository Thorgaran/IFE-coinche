#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "cardUtils.h"
#include "userIO.h"
#include "ai.h"

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

int getCardArrayPoints(Card *cardArray, int nbOfCards, Color trump) {
    int totalPoints = 0;
    for (int i = 0; i < nbOfCards; i++) {
        totalPoints += getCardPoints(cardArray[i], trump);
    }
    return totalPoints;
}

Bool setCanPlay(Card *cardArray, int nbOfCards, Color conditionalColor, Color trump, int bestTrumpStrength, Bool canPlay) {
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

void findValidCardsInHand(Card *cardsInHand, int nbOfCardsInHand, Card *trickCards, int nbOfTrickCards, Color trump) {
    Bool canFollow;
    Card bestCard;
    int bestTrumpStrength = 0;

    if (nbOfTrickCards == 0) {                                                                                      //The first player of a trick
        setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, trump, 0, TRUE);                                       //can play any card.
    }
    else {
        if (trump == ALLTRUMP) {
            trump = trickCards[0].color;                                                                            //This line is what makes this function work when the trump is ALLTRUMP
        }
        bestCard = trickCards[getStrongestCard(trickCards, nbOfTrickCards, trump, NULL_COLOR)];                     //Find the best card on the table
        if (bestCard.color == trump) {                                                                              //If it's a trump,
            bestTrumpStrength = getCardStrength(bestCard, trump, NULL_COLOR);                                       //update bestTrumpStrength
        }
        setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, trump, 0, FALSE);                                      //Each card is initialised to canPlay = FALSE
        canFollow = setCanPlay(cardsInHand, nbOfCardsInHand, trickCards[0].color, trump, bestTrumpStrength, TRUE);  //A player must follow in the right color. If that color is a trump, the player has to play a stronger card. 
        if ((trickCards[0].color == trump) && (canFollow == FALSE)) {                                               //If the trick was started with a trump AND playing a higher trump than the current best one is impossible,
            canFollow = setCanPlay(cardsInHand, nbOfCardsInHand, trump, trump, 0, TRUE);                            //the player has to follow with a lower trump.
        }
        if (canFollow == FALSE) {                                                                                   //If playing in the right color is impossible:
            if (getStrongestCard(trickCards, nbOfTrickCards, trump, trickCards[0].color) == (nbOfTrickCards - 2)) { //If the player's partner is the current trick winner,
                setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, trump, 0, TRUE);                               //any card can be played.
            }
            else {
                canFollow = setCanPlay(cardsInHand, nbOfCardsInHand, trump, trump, bestTrumpStrength, TRUE);        //A player must play a stronger trump card than the current best one if its partner isn't winning.
                if (canFollow == FALSE) {                                                                           //If all of the above are impossible,
                    setCanPlay(cardsInHand, nbOfCardsInHand, NULL_COLOR, trump, 0, TRUE);                           //the player can play any card.
                }
            }
        }
    }    
}

Card getPlayerCard(Player *player, Card *trickCards, int nbOfTrickCards, Color trump, Color roundColor) {
    Card chosenCard;
    switch ((*player).type) {
        case USER: //If the player is the User
            chosenCard = askUserCard((*player).cards, (*player).nbOfCards);
            break;
        case AI_FIRSTAVAILABLE: //If the player is an AI of type FIRSTAVAILABLE
            chosenCard = getAICardFirstAvailable((*player).cards, (*player).nbOfCards);
            break;
        case AI_STANDARD: //If the player is an AI of type STANDARD
            chosenCard = getAICardStandard((*player).cards, (*player).nbOfCards, trickCards, nbOfTrickCards, trump, roundColor);
            break;
        default: //Default behaviour if the AI type isn't recognised
            chosenCard = getAICardStandard((*player).cards, (*player).nbOfCards, trickCards, nbOfTrickCards, trump, roundColor);
    }
    removeCard((*player).cards, &((*player).nbOfCards), chosenCard); //Once a card has been chosen, remove it from the player's hand
    return chosenCard;
}

Position playTrick(Player *players, Position startingPlayer, Color trump) {
    Card trickCards[4];
    Color roundColor = NULL_COLOR;
    Position trickWinner;
    for (int i = 0; i < 4; i++) { //4 iterations because each player will play a card
        findValidCardsInHand(players[(i+startingPlayer)%4].cards, players[(i+startingPlayer)%4].nbOfCards, trickCards, i, trump); //Find valid cards in the hand of the current player
        for (int j = 0; j < players[(i+startingPlayer)%4].nbOfCards; j++) { //TEMP DEBUG FEEDBACK
            printf("%d ", players[(i+startingPlayer)%4].cards[j].canPlay);  //TEMP DEBUG FEEDBACK
        }                                                                   //TEMP DEBUG FEEDBACK
        printf("\n");                                                       //TEMP DEBUG FEEDBACK
        trickCards[i] = getPlayerCard(&(players[(i+startingPlayer)%4]), trickCards, i, trump, roundColor);
        if (i == 0) {
            roundColor = trickCards[0].color;
        }
    }
    trickWinner = (getStrongestCard(trickCards, 4, trump, roundColor) + startingPlayer) % 4;
    //getStrongestCard returns a relative value while trickWinner an absolute position, hence the conversion with startingPlayer and a modulo
    players[trickWinner].score += getCardArrayPoints(trickCards, 4, trump); //Increase the score of the trick winner
    printf("Player %d wins the trick and gets %d points, for a total of %d!\n", trickWinner, getCardArrayPoints(trickCards, 4, trump), players[trickWinner].score); //TEMP DEBUG FEEDBACK
    return trickWinner;
}

void play(Player *players, Position startingPlayer, Color trump) {
    for (int i = 0; i < 8; i++) {   //plays the 8 tricks of a game
        startingPlayer = playTrick(players, startingPlayer, trump); //the previous trick winner becomes the starting player
    }
    players[startingPlayer].score += 10; //10 bonus points for the last trick's winner
}