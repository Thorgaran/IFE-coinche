#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "cardUtils.h"
#include "userIO.h"
#include "ai.h"

Card getPlayerCard(Player *player, Card trickCards[], int nbOfTrickCards, Color trump, Color roundColor) {
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
        default: //Default behaviour if this AI type has no dedicated card function
            chosenCard = getAICardStandard((*player).cards, (*player).nbOfCards, trickCards, nbOfTrickCards, trump, roundColor);
    }
    removeCard((*player).cards, &((*player).nbOfCards), chosenCard); //Once a card has been chosen, remove it from the player's hand
    return chosenCard;
}

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

int getTeamPoints(Player players[], Position trickWinner) {
    return 0;
}