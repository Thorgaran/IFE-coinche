#include <stdio.h>
#include <stdlib.h>
#include "userIO.h"

Card askUserCard(Card cardArray[], int nbOfCards) {
    Card chosenCard = {.color = SPADE, .value = SEVEN};
    return chosenCard;
}

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract) {
    Bool hasPassed = TRUE;
    return hasPassed;
}

void displayCard(Card card) {
    printf("\u256d\u2500\u2500\u2500\u256e\033[5D\033[1B"); //╭───╮
    printf("\u2502   \u2502\033[5D\033[1B");                //│   │
    printf("\u2502   \u2502\033[5D\033[1B");                //│   │
    printf("\u2570\u2500\u2500\u2500\u256f\033[5D\033[3A"); //╰───╯
    changeCardDisplay(card); //Fill in the card
}

void changeCardDisplay(Card card) {
    printf("\033[1C\033[1B%s\033[1B%s\033[4D\033[2A", VALUE_STR_TABLE[card.value], COLOR_STR_TABLE[card.color]);
    //Change the value, then the color, then return the cursor to the top-left of the card
}

void displayTrick(Player* players, Color trump, Contract contract) {
    printf("Trick 1/8\nTrump : %d", trump);
    switch (contract.type) {
        case POINTS:
            printf("\n%d points %d contract in %d made by %d\n\n", contract.points, contract.coinche, contract.trump, contract.issuer);
            break;
        default:
            printf("\n%d %d contract in %d made by %d\n\n", contract.type, contract.coinche, contract.trump, contract.issuer);
            break;
    }
    printf("\t\t\t\tNorth\n\n\t\t\t\t \nWest\t \t\t\t\t \tEast\n\t\t\t\t \n\t\t\t   %s", players[SOUTH].name);
    printf("\n\nYour hand : ");
    for (int cardNb = 0; cardNb < 8; cardNb++) {
        printf("%d%d ", players[SOUTH].cards[cardNb].value, players[SOUTH].cards[cardNb].color);
    }
}

void updateTrickDisplay(Position playerPosition, Card playedCard, Card* playerHand, int nbOfCardsInHand) {
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