#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"
#include "play.h"
#include "cardUtils.h"

int main (int argc, char* argv[]) {
    srand(time(0)); //Initialize the random function

    Card playersCards[4][8];
    Player players[4];
    for (Position pos = SOUTH; pos <= EAST; pos++) {
        players[pos].cardAI = CARD_AI_STANDARD;
        players[pos].contractAI = CONTRACT_AI_STANDARD;
        players[pos].pos = pos;
        players[pos].teamScore = 0;
        players[pos].cards = playersCards[pos];
    }

    playGame(players);

    getchar();
    return EXIT_SUCCESS;
}