#include <stdlib.h>
#include <stdio.h>
#include "play.h"
#include "cardUtils.h"
#include "displayRound.h"
#include "playerUtils.h"
#include "userInput.h"

Bool bidAttempt(Player players[], Position startingPlayer, Contract *contract) {
    Position currentPlayer = startingPlayer; //Transferring startingPlayer to currentPlayer
    Bool hasPassed, everyonePassed = TRUE; //everyonePassed starts at TRUE and will be set to FALSE as soon as someone makes a contract
    int nbOfConsecutivePass = 0;
    char displayMsg[70]; //Only used in display mode
    do {
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            displayPlayerName(players[currentPlayer], TRUE); //Add underline to the active player
        }
        hasPassed = getPlayerContract(players[currentPlayer], contract); //Get the player to decide on a contract or pass
        if (hasPassed == TRUE) {        //If the player passed,
            nbOfConsecutivePass++;      //increase the number of consecutive pass
            if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
                sprintf(displayMsg, "%s decided to pass.", players[currentPlayer].croppedName);
                inputUserAcknowledgement(displayMsg);
                displayPlayerName(players[currentPlayer], FALSE); //Remove underline from the active player
            }
        }
        else {                          //If the player didn't pass,
            nbOfConsecutivePass = 0;    //Reset the number of consecutive pass
            everyonePassed = FALSE;     //If everyonePassed is still on TRUE, set it to FALSE
            if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
                updateContractDisplay(players[currentPlayer].name, *contract); //Update the contract display with the new contract
                if (contract->coinche == NOT_COINCHED) { //If the contract wasn't just coinched or overcoinched
                    sprintf(displayMsg, "%s made a%s contract.", players[currentPlayer].croppedName, COLOR_STR_TABLE[contract->trump][1]);
                    //The color of the contract will be displayed in either red or white
                }
                else { //If the contract has just been coinched or overcoinched
                    sprintf(displayMsg, "Contract %s from %s!", COINCHE_STR_TABLE[contract->coinche], players[currentPlayer].croppedName);
                }
                inputUserAcknowledgement(displayMsg);
                displayPlayerName(players[currentPlayer], FALSE); //Remove underline from the active player
            }
        }
        currentPlayer = (currentPlayer + 1) % 4; //Go to next player
    } while (((nbOfConsecutivePass < 3) || ((everyonePassed == TRUE) && (nbOfConsecutivePass < 4))) && (contract->coinche != OVERCOINCHED));
    //While no three players passed in a row OR it's still the first turn AND no four players passed in a row, AND there was no overcoinche
    return everyonePassed;
}

Contract bidUntilContract(Player players[], Position startingPlayer) {
    Contract contract = {.points = 0, .coinche = NOT_COINCHED, .type = POINTS}; //Contract is initialized
    Bool everyonePassed;
    do {
        cardsDistribution(players);
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            displayPlayerHand(players[SOUTH].cards, 8); //Display the hand without numbers above it
        }
        everyonePassed = bidAttempt(players, startingPlayer, &contract); //Do a bid attempt
    } while (everyonePassed == TRUE); //As long as no contract is made, repeat the loop
    return contract;
}

Position playTrick(Player players[], Position startingPlayer, Color trump) {
    Card trickCards[4];
    Color roundColor = NULL_COLOR; //The round color is null at first because the first player can play any card
    Position currentPlayer, trickWinner;
    char displayMsg[53]; //Only used in display mode
    for (int i = 0; i < 4; i++) { //4 iterations because each player will play a card
        currentPlayer = (i+startingPlayer)%4; //Compute the absolute position of the current player
        findValidCardsInHand(players[currentPlayer].cards, players[currentPlayer].nbOfCards, trickCards, i, trump); //Find valid cards in the hand of the current player
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            displayPlayerName(players[currentPlayer], TRUE); //Add underline to the active player
        }
        trickCards[i] = getPlayerCard(&(players[currentPlayer]), trickCards, i, trump, roundColor);
        if (i == 0) {                           //If the first card was just played,
            roundColor = trickCards[0].color;   //change the round color to its actual value
        }
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            displayTrickCard(trickCards[i], currentPlayer);
            if (players[currentPlayer].cardAI == CARD_USER) {                 //If the current player is the user,
                displayPlayerHand(players[SOUTH].cards, players[SOUTH].nbOfCards);   //update its hand with one less card
            }
            else {
                sprintf(displayMsg, "%s played a %s of%s.", players[currentPlayer].croppedName, VALUE_STR_TABLE[trickCards[i].value][1], COLOR_STR_TABLE[trickCards[i].color][1]);
                inputUserAcknowledgement(displayMsg);
            }
            displayPlayerName(players[currentPlayer], FALSE); //Remove underline from the active player
        }
    }
    trickWinner = (getStrongestCard(trickCards, 4, trump, roundColor) + startingPlayer) % 4;
    //getStrongestCard returns a relative value while trickWinner needs an absolute position, hence the conversion with startingPlayer and a modulo
    players[trickWinner].score += getCardArrayPoints(trickCards, 4, trump); //Increase the score of the trick winner
    if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
        updatePlayerTrickPoints(players[trickWinner].score, trickWinner);
        updateLastTrickDisplay(trickCards, startingPlayer);
        deleteDisplayedTrickCards();
        sprintf(displayMsg, "%s won the trick.", players[trickWinner].croppedName);
        inputUserAcknowledgement(displayMsg);
    }
    return trickWinner;
}

void playRound(Player players[], Position startingPlayer, Color trump) {
    char displayMsg[20]; //Only used in display mode
    for (int i = 0; i < 8; i++) { //Plays the 8 tricks of a round
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            updateTrickNbDisplay(i + 1); //Update the displayed trick number
            sprintf(displayMsg, "Trick %d begins.", i+1);
            inputUserAcknowledgement(displayMsg);
        }
        startingPlayer = playTrick(players, startingPlayer, trump); //The previous trick winner becomes the starting player
    }
    players[startingPlayer].score += 10; //10 bonus points for the last trick's winner
}

void awardTeamPoints(Player players[], Contract contract) {
    Position defendant = (contract.issuer + 1) % 4;
    int issuerTeamScore, defendantTeamScore;
    int issuerTeamPoints = getTeamRoundPoints(players, contract.issuer);
    char displayMsg[54];
    if (((contract.type == POINTS) && (issuerTeamPoints >= contract.points) && (issuerTeamPoints >= 82)) ||
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
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            sprintf(displayMsg, "%s fulfilled the contract!", players[contract.issuer].croppedName);
            inputUserAcknowledgement(displayMsg);
        }
    }
    else { //If the contract isn't fulfilled
        defendantTeamScore = 162 + contract.points;             //total defendant score = 162 + contract points
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
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            sprintf(displayMsg, "%s didn't fulfill the contract.", players[contract.issuer].croppedName);
            inputUserAcknowledgement(displayMsg);
        }
    }
}

int playGame(Player players[]) {
    Contract contract;
    Position startingPlayer = rand() % 4;
    int currentRound = 0;
    char displayMsg[20]; //Only used in display mode
    for (Position pos = SOUTH; pos <= EAST; pos++) {    //For each player,
        players[pos].teamScore = 0;                     //Set its team score to 0
    }
    if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
        preparePlayTable();
        for (Position pos = SOUTH; pos <= EAST; pos++) {    //For each player,
            displayPlayerName(players[pos], FALSE);         //display their name
        }
    }
    do {
        currentRound++;                                         //Increment the current round
        startingPlayer = (startingPlayer + 1) % 4;              //Change the starting player
        for (Position pos = SOUTH; pos <= EAST; pos++) {        //For each player,
            players[pos].score = 0;                             //reset its score,
            players[pos].nbOfCards = 8;                         //and its number of cards
        }
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            updateRoundNbDisplay(currentRound);
            updateTrickNbDisplay(0); //Display " Bidding "
            clearContractDisplay();
            clearLastTrickDisplay();
            sprintf(displayMsg, "Round %d begins.", currentRound);
            inputUserAcknowledgement(displayMsg);
        }
        contract = bidUntilContract(players, startingPlayer);   //Do bidding until a contract is made
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            prepareLastTrickDisplay();
            for (Position pos = SOUTH; pos <= EAST; pos++) {    //For each player,
                updatePlayerTrickPoints(0, pos);                //Display a score of 0
            }
        }
        playRound(players, startingPlayer, contract.trump);     //Play an 8-tricks round
        awardTeamPoints(players, contract);                     //Award team points depending on whether or not the contract was fulfilled
        if (players[SOUTH].cardAI == CARD_USER) { //Display stuff if the game has a playing user
            updateTeamScore(players);
            clearDisplayedTrickPoints();
        }
    } while ((players[0].teamScore <= 700) && (players[1].teamScore <= 700)); //Repeat until a team reaches 701 points
    return currentRound;
}

float playAIGames(Player players[], int nbOfGames, int nbOfGamesWon[]) {
    long totalNbOfRounds = 0;
    float averageGameLength;
    for (int game = 0; game < nbOfGames; game++) {  //Play "nbOfGames" games
        totalNbOfRounds += playGame(players);       //Play a game and increase the total number of rounds
        if (players[SOUTH].teamScore > 700) {       //If the first team won,
            nbOfGamesWon[0] += 1;                   //increase its number of wins
        }
        else {
            nbOfGamesWon[1] += 1;                   //Else, increase the second team's number of wins
        }
    }
    averageGameLength = totalNbOfRounds / (float)nbOfGames;
    return averageGameLength;
}