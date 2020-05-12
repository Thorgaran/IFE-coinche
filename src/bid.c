#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "userIO.h"
#include "ai.h"

Bool getPlayerContract(Player player, Contract *contract) {
    Bool hasPassed = TRUE;
    switch (player.type) {
        case USER: //If the player is the User
            hasPassed = askUserContract(player.cards, player.nbOfCards, &(*contract));
            break;
        case AI_STANDARD: //If the player is an AI of type STANDARD
            hasPassed = getAIContractStandard(player.cards, player.nbOfCards, &(*contract));
            break;
        default: //Default behaviour if this AI type has no dedicated contract function
            hasPassed = getAIContractStandard(player.cards, player.nbOfCards, &(*contract));
    }
    if (hasPassed == FALSE) { //If the player decided to make a contract
        (*contract).issuer = player.pos; //Set the contract issuer as being this player
    }
    return hasPassed;
}

Bool bidAttempt(Player players[], Position startingPlayer, Contract *contract) {
    Position currentPlayer = startingPlayer; //Transferring startingPlayer to currentPlayer
    Bool hasPassed, everyonePassed = TRUE; //everyonePassed starts at TRUE and will be set to FALSE as soon as someone makes a contract
    int nbOfConsecutivePass = 0;
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

Contract bid(Player players[], Position startingPlayer) {
    Contract contract = {.points = 0, .coinche = NOT_COINCHED}; //Contract is initialized
    Bool everyonePassed;
    do {
        //REPLACE THIS LINE WITH THE CARD DEALING FUNCTION
        everyonePassed = bidAttempt(players, startingPlayer, &contract); //Do a bid attempt
    } while (everyonePassed == TRUE); //As long as no contract is made, repeat the loop
    return contract;
}