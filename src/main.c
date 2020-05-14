#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"
#include "play.h"
#include "cardUtils.h"

int main (int argc, char* argv[]) {
    srand(time(0)); //Initialize the random function

    Card playersCards[4][8];
    Player player0 = {.type = AI_STANDARD, .pos = SOUTH, .score = 0, .nbOfCards = 8, .cards = playersCards[0]};
    Player player1 = {.type = AI_STANDARD, .pos = WEST,  .score = 0, .nbOfCards = 8, .cards = playersCards[1]};
    Player player2 = {.type = AI_STANDARD, .pos = NORTH, .score = 0, .nbOfCards = 8, .cards = playersCards[2]};
    Player player3 = {.type = AI_STANDARD, .pos = EAST,  .score = 0, .nbOfCards = 8, .cards = playersCards[3]};
    Player players[] = {player0, player1, player2, player3};
    
    Contract contract;
    Position startingPlayer = SOUTH;

    contract = bidUntilContract(players, startingPlayer);

    playRound(players, startingPlayer, contract.trump);
    for (int i = 0; i < 4; i++) {
        printf("Player %d has %d points!\n", i, players[i].score);    
    }
    printf("\n");

    awardTeamPoints(players, contract);
    printf("Team SOUTH + NORTH has a score of %d!\n", players[0].teamScore);
    printf("Team  WEST + EAST  has a score of %d!\n", players[1].teamScore);

    getchar();
    return EXIT_SUCCESS;
}