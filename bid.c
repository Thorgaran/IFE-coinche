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