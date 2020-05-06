#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "play.h"
#include "cardUtils.h"

int main (int argc, char* argv[]) {
    /*Card player0cards[8] =
        {{.value = ACE,   .color = HEART},
        { .value = ACE,   .color = SPADE},
        { .value = QUEEN, .color = HEART},
        { .value = EIGHT, .color = SPADE},
        { .value = QUEEN, .color = DIAMOND},
        { .value = NINE,  .color = HEART},
        { .value = JACK,  .color = CLUB},
        { .value = QUEEN, .color = CLUB}};

    Card player1cards[8] =
        {{.value = JACK,  .color = HEART},
        { .value = KING,  .color = SPADE},
        { .value = NINE,  .color = CLUB},
        { .value = TEN,   .color = SPADE},
        { .value = SEVEN, .color = DIAMOND},
        { .value = JACK,  .color = DIAMOND},
        { .value = SEVEN, .color = CLUB},
        { .value = ACE,   .color = CLUB}};
    
    Card player2cards[8] =
        {{.value = TEN,   .color = HEART},
        { .value = QUEEN, .color = SPADE},
        { .value = SEVEN, .color = HEART},
        { .value = JACK,  .color = SPADE},
        { .value = TEN,   .color = DIAMOND},
        { .value = ACE,   .color = DIAMOND},
        { .value = KING,  .color = HEART},
        { .value = TEN,   .color = CLUB}};
    
    Card player3cards[8] =
        {{.value = EIGHT, .color = HEART},
        { .value = SEVEN, .color = SPADE},
        { .value = KING,  .color = DIAMOND},
        { .value = NINE,  .color = SPADE},
        { .value = EIGHT, .color = DIAMOND},
        { .value = NINE,  .color = DIAMOND},
        { .value = EIGHT, .color = CLUB},
        { .value = KING,  .color = CLUB}};

    Player player0 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player0cards};
    Player player1 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player1cards};
    Player player2 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player2cards};
    Player player3 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player3cards};

    Player players[] = {player0, player1, player2, player3};

    play(players, 0, CLUB);
    
    for (int i = 0; i < 4; i++) {
        printf("Player %d has %d points!\n", i, players[i].score);    
    }*/
    CardsDistribution();
    getchar();

    ;
    return EXIT_SUCCESS;
}