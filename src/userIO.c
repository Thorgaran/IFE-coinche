#include <stdio.h>
#include <stdlib.h>
#include "core.h"

Card askUserCard(Card cardArray[], int nbOfCards) {
    Card chosenCard = {.color = SPADE, .value = SEVEN};
    return chosenCard;
}

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract) {
    Bool hasPassed = TRUE;
    return hasPassed;
}

void displayTrick(Player* players,Color trump, int nbOfTheTrick, Contract contract, Card* playerHand){
    
    printf("Trick %d / 8\nTrump : %d",nbOfTheTrick,trump);
    switch (contract.type){
    case POINTS: printf("\n%d points %d contract in %d made by %d\n\n",contract.points,contract.coinche,contract.trump,contract.issuer);
        break;
    
    default: printf("\n%d %d contract in %d made by %d\n\n",contract.type,contract.coinche,contract.trump,contract.issuer);
        break;
    }
    printf("\t\t\t\tNorth\n\n\t\t\t\t \nWest\t \t\t\t\t \tEast\n\t\t\t\t \n\t\t\t   %s",players[0].name);
    printf("\n\nYour hand : ");
    for (int cardNb = 0; cardNb < 8; cardNb++){
    printf("%d%d ",playerHand[cardNb].value,playerHand[cardNb].color);
    }
    
}

void updateTrickDisplay(Position playerPosition,Card playedCard, Card* playerHand, int nbOfCardsInHand){
    switch (playerPosition)
    {
    case NORTH: printf("\e[5;18H");
        break;
    case SOUTH: printf("\e[10;18H");
        break;
    case WEST: printf("\e[8;10H");
        break;
    case EAST: printf("\e[8;24H");
        break;
    }
    printf("%d%d",playedCard.value,playedCard.color);
    printf("\e[13;13H");
    for (int cardNb = 0; cardNb < nbOfCardsInHand; cardNb++){
    printf("%d%d ",playerHand[cardNb].value,playerHand[cardNb].color);
    }
}