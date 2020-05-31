#include <stdio.h>
#include <stdlib.h>
#include "userIO.h"

int inputUserInt(int minBound, int maxBound, char* displayStr) {
    char buffer[5];
    char* endPtr;
    int userVal = -1;
    long userValLong;
    do {
        printf("\e[1;1H\e[2J");
        printf(displayStr);
        if (fgets(buffer, 5, stdin) != NULL) {
            userValLong = strtol(buffer, &endPtr, 10);
            if ((endPtr != buffer) && (userValLong >= minBound) && (userValLong <= maxBound)) { //The condition order is very important!
            //If the address pointed to by endPtr isn't the first one of the buffer (so if reading a long was successful), and the value is between the bounds
                userVal = userValLong;
            }
        }
    } while (userVal == -1);
    return userVal;
}

Card askUserCard(Card cardArray[], int nbOfCards) {
    Card chosenCard = {.color = SPADE, .value = SEVEN};
    return chosenCard;
}

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract) {
    Bool hasPassed = TRUE;
    return hasPassed;
}