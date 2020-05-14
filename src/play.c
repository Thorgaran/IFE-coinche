#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "cardUtils.h"
#include "playerUtils.h"



void findValidCardsInHand(Card cardsInHand[], int nbOfCardsInHand, Card trickCards[], int nbOfTrickCards, Color trump) {
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

Position playTrick(Player players[], Position startingPlayer, Color trump) {
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

void playRound(Player players[], Position startingPlayer, Color trump) {
    for (int i = 0; i < 8; i++) { //Plays the 8 tricks of a round
        startingPlayer = playTrick(players, startingPlayer, trump); //The previous trick winner becomes the starting player
    }
    players[startingPlayer].score += 10; //10 bonus points for the last trick's winner
}

void awardTeamPoints(Player players[], Contract contract) {
    Position defendant = (contract.issuer + 1) % 4;
    int issuerTeamScore, defendantTeamScore;
    int issuerTeamPoints = getTeamRoundPoints(players, contract.issuer);
    if (((contract.type == POINTS) && (issuerTeamPoints >= contract.points)) ||
        ((contract.type == CAPOT) && (issuerTeamPoints == 162)) ||
        ((contract.type == GENERAL) && (players[contract.issuer].score == 162))) {  //If the contract is fulfilled,
        issuerTeamScore = issuerTeamPoints + contract.points;                       //total issuer score = trick points + contract point value
        switch (contract.coinche) {
            case COINCHED:                              //If the contract was coinched,
                issuerTeamScore = issuerTeamScore * 2;  //double the score,
                break;                                  //and the defendant team gets nothing
            case OVERCOINCHED:                          //If the contract was overcoinched,
                issuerTeamScore = issuerTeamScore * 4;  //multiply the score by 4,
                break;                                  //and the defendant team gets nothing
            default:                                                            //Otherwise,
                defendantTeamScore = getTeamRoundPoints(players, defendant);    //the defendant team gets it's round points
                increaseTeamTotalScore(players, defendant, defendantTeamScore);
                break;
        }
        increaseTeamTotalScore(players, contract.issuer, issuerTeamScore); //Increase the issuer's team total score
    }
    else { //If the contract isn't fulfilled
        defendantTeamScore =  getTeamRoundPoints(players, defendant) + 162;    //total defendant score = trick points + 162
        switch (contract.coinche) {
            case COINCHED:                                      //If the contract was coinched,
                defendantTeamScore = defendantTeamScore * 2;    //double the score
                break;
            case OVERCOINCHED:                                  //If the contract was overcoinched,
                defendantTeamScore = defendantTeamScore * 4;    //multiply the score by 4
                break;
            default:                                            //Otherwise, do nothing
                break;
        }
        increaseTeamTotalScore(players, defendant, defendantTeamScore); //Increase the defendant's team total score, and the issuer's team gets nothing
    }
}
