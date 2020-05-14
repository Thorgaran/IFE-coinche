#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "cardUtils.h"
#include "playerUtils.h"

Bool bidAttempt(Player players[], Position startingPlayer, Contract *contract) {
    Position currentPlayer = startingPlayer; //Transferring startingPlayer to currentPlayer
    Bool hasPassed, everyonePassed = TRUE; //everyonePassed starts at TRUE and will be set to FALSE as soon as someone makes a contract
    int nbOfConsecutivePass = 0;
    printf("New bid attempt...\n"); //TEMP DEBUG FEEDBACK
    do {
        hasPassed = getPlayerContract(players[currentPlayer], &(*contract)); //Get the player to decide on a contract or pass
        if (hasPassed == TRUE) {        //If the player passed,
            nbOfConsecutivePass++;      //increase the number of consecutive pass
            printf("Player %d didn't make a contract.\n", currentPlayer); //TEMP DEBUG FEEDBACK
        }
        else {                          //If the player didn't pass,
            nbOfConsecutivePass = 0;    //Reset the number of consecutive pass
            everyonePassed = FALSE;     //If everyonePassed is still on TRUE, set it to FALSE
            printf("Player %d decided to make a %d \"%d\" contract!\n", currentPlayer, (*contract).points, (*contract).trump - 1); //TEMP DEBUG FEEDBACK
        }
        currentPlayer = (currentPlayer + 1) % 4; //Go to next player
    } while (((nbOfConsecutivePass < 3) || ((everyonePassed == TRUE) && (nbOfConsecutivePass < 4))) && ((*contract).coinche != OVERCOINCHED));
    //While no three players passed in a row OR it's still the first turn AND no four players passed in a row, AND there was no overcoinche
    return everyonePassed;
}

Contract bidUntilContract(Player players[], Position startingPlayer) {
    Contract contract = {.points = 0, .coinche = NOT_COINCHED, .type = POINTS}; //Contract is initialized
    Bool everyonePassed;
    do {
        cardsDistribution(players);
        everyonePassed = bidAttempt(players, startingPlayer, &contract); //Do a bid attempt
    } while (everyonePassed == TRUE); //As long as no contract is made, repeat the loop
    return contract;
}

Position playTrick(Player players[], Position startingPlayer, Color trump) {
    Card trickCards[4];
    Color roundColor = NULL_COLOR;
    Position trickWinner;
    for (int i = 0; i < 4; i++) { //4 iterations because each player will play a card
        findValidCardsInHand(players[(i+startingPlayer)%4].cards, players[(i+startingPlayer)%4].nbOfCards, trickCards, i, trump); //Find valid cards in the hand of the current player
        trickCards[i] = getPlayerCard(&(players[(i+startingPlayer)%4]), trickCards, i, trump, roundColor);
        if (i == 0) {
            roundColor = trickCards[0].color;
        }
    }
    trickWinner = (getStrongestCard(trickCards, 4, trump, roundColor) + startingPlayer) % 4;
    //getStrongestCard returns a relative value while trickWinner an absolute position, hence the conversion with startingPlayer and a modulo
    players[trickWinner].score += getCardArrayPoints(trickCards, 4, trump); //Increase the score of the trick winner
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

void playGame(Player players[]) {
    Contract contract;
    Position startingPlayer = rand() % 4;
    do {
        startingPlayer = (startingPlayer + 1) % 4;
        for (Position pos = SOUTH; pos <= EAST; pos++) {    //For each player,
            players[pos].score = 0;                         //reset its score,
            players[pos].nbOfCards = 8;                     //and its number of cards
        }
        printf("-------------- NEW ROUND --------------\n");                        //TEMP DEBUG FEEDBACK
        contract = bidUntilContract(players, startingPlayer);   //Do bidding until a contract is made
        playRound(players, startingPlayer, contract.trump);     //Play an 8-tricks round
        for (int i = 0; i < 4; i++) {                                               //TEMP DEBUG FEEDBACK
            printf("Player %d has %d points!\n", i, players[i].score);              //TEMP DEBUG FEEDBACK
        }                                                                           //TEMP DEBUG FEEDBACK
        awardTeamPoints(players, contract); //Award team points depending on whether or not the contract was fulfilled
        printf("Team SOUTH + NORTH has a score of %d!\n", players[0].teamScore);    //TEMP DEBUG FEEDBACK
        printf("Team  WEST + EAST  has a score of %d!\n\n", players[1].teamScore);  //TEMP DEBUG FEEDBACK
    } while ((players[0].teamScore < 700) && (players[1].teamScore < 700)); //Repeat until a team reaches 700 points
}