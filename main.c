#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "play.h"

int main (int argc, char* argv[]) {
    cardType player0cards[8] =
        {{.value = SEVEN, .color = SPADE},
        { .value = EIGHT, .color = HEART},
        { .value = NINE,  .color = DIAMOND},
        { .value = JACK,  .color = CLUB},
        { .value = QUEEN, .color = SPADE},
        { .value = KING,  .color = HEART},
        { .value = TEN,   .color = DIAMOND},
        { .value = ACE,   .color = CLUB}};

    cardType player1cards[8] =
        {{.value = SEVEN, .color = HEART},
        { .value = EIGHT, .color = DIAMOND},
        { .value = NINE,  .color = CLUB},
        { .value = JACK,  .color = SPADE},
        { .value = QUEEN, .color = HEART},
        { .value = KING,  .color = DIAMOND},
        { .value = TEN,   .color = CLUB},
        { .value = ACE,   .color = SPADE}};
    
    cardType player2cards[8] =
        {{.value = SEVEN, .color = DIAMOND},
        { .value = EIGHT, .color = CLUB},
        { .value = NINE,  .color = SPADE},
        { .value = JACK,  .color = HEART},
        { .value = QUEEN, .color = DIAMOND},
        { .value = KING,  .color = CLUB},
        { .value = TEN,   .color = SPADE},
        { .value = ACE,   .color = HEART}};
    
    cardType player3cards[8] =
        {{.value = SEVEN, .color = CLUB},
        { .value = EIGHT, .color = SPADE},
        { .value = NINE,  .color = HEART},
        { .value = JACK,  .color = DIAMOND},
        { .value = QUEEN, .color = CLUB},
        { .value = KING,  .color = SPADE},
        { .value = TEN,   .color = HEART},
        { .value = ACE,   .color = DIAMOND}};

    Player player0 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player0cards};
    Player player1 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player1cards};
    Player player2 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player2cards};
    Player player3 = {.isUser = FALSE, .score = 0, .nbOfCards = 8, .cards = player3cards};

    Player players[] = {player0, player1, player2, player3};

    play(players, 0, HEART);
    
    for (int i = 0; i < 4; i++) {
        printf("Player %d has %d points!\n", i, players[i].score);    
    }
    
    getchar();
    return EXIT_SUCCESS;
}