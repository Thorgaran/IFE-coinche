#include <stdio.h>
#include <stdlib.h>
#include "playerUtils.h"
#include "cardUtils.h"
#include "userIO.h"
#include "ai.h"

Card getPlayerCard(Player *player, Card trickCards[], int nbOfTrickCards, Color trump, Color roundColor) {
    Card chosenCard;
    switch (player->cardAI) {
        case CARD_USER: //If the player is the User
            chosenCard = askUserCard(player->cards, player->nbOfCards);
            break;
        case CARD_AI_FIRSTAVAILABLE: //If the player is an AI of type FIRSTAVAILABLE
            chosenCard = getAICardFirstAvailable(player->cards, player->nbOfCards);
            break;
        case CARD_AI_STANDARD: //If the player is an AI of type STANDARD
            chosenCard = getAICardStandard(player->cards, player->nbOfCards, trickCards, nbOfTrickCards, trump, roundColor);
            break;
        default: //Default behaviour if this AI type has no dedicated card function
            chosenCard = getAICardStandard(player->cards, player->nbOfCards, trickCards, nbOfTrickCards, trump, roundColor);
    }
    removeCard(player->cards, &(player->nbOfCards), chosenCard); //Once a card has been chosen, remove it from the player's hand
    return chosenCard;
}

Bool getPlayerContract(Player player, Contract *contract) {
    Bool hasPassed = TRUE;
    switch (player.contractAI) {
        case CONTRACT_USER: //If the player is the User
            hasPassed = askUserContract(player.cards, player.nbOfCards, contract);
            break;
        case CONTRACT_AI_ALWAYSEIGHTY: //If the player is an AI of type ALWAYSEIGHTY
            hasPassed = getAIContractAlwaysEighty(player.cards, contract);
            break;
        case CONTRACT_AI_STANDARD: //If the player is an AI of type STANDARD
            hasPassed = getAIContractStandard(player.cards, player.nbOfCards, contract);
            break;
        default: //Default behaviour if this AI type has no dedicated contract function
            hasPassed = getAIContractStandard(player.cards, player.nbOfCards, contract);
    }
    if (hasPassed == FALSE) { //If the player decided to make a contract
        contract->issuer = player.pos; //Set the contract issuer as being this player
    }
    return hasPassed;
}

void cardsDistribution(Player players[]) {
    Card cardDeck[32];
    int randomCardNb;
    int nbOfRemainingCards = 32;
    createDeck(cardDeck); //Prepare the full deck that will be dealed
    for (int cardIndex = 0; cardIndex < 8; cardIndex++) {
        for (Position player = SOUTH; player <= EAST; player++) {
            randomCardNb = rand()%(nbOfRemainingCards);                         //Choose a card among the remaining ones
            players[player].cards[cardIndex] = cardDeck[randomCardNb];          //Give that card to the player,
            removeCard(cardDeck, &nbOfRemainingCards, cardDeck[randomCardNb]);  //and remove it from the deck
        } 
    }
}

int getTeamRoundPoints(Player players[], Position player) {
    int roundPoints = players[player].score;        //Get the player's points
    roundPoints += players[(player + 2) % 4].score; //Get its partner's points
    return roundPoints;
}

void increaseTeamTotalScore(Player players[], Position player, int roundScore) {
    players[player].teamScore += roundScore;            //Increase the player's total team score
    players[(player + 2) % 4].teamScore += roundScore;  //Increase its partner's total team score
}

void createPlayersCroppedNames(Player players[]) {
    char* croppedName = NULL;
    for (Position pos = SOUTH; pos <= EAST; pos++) {    //For each player,
        croppedName = cropStr(players[pos].name, 15);   //create its cropped name,
        players[pos].croppedName = croppedName;         //and save it
    }
}