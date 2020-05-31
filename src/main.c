#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "core.h"
#include "play.h"
#include "cardUtils.h"
#include "userIO.h"
#include "ansi.h"

int main (int argc, char* argv[]) {
    srand(time(0)); //Initialize the random function
    setlocale (LC_ALL, "");
    setupConsole();

    /*float averageGameLength;
    int nbOfGamesWon[] = {0, 0};*/

    Card playersCards[4][8];
    Player players[4];
    for (Position pos = SOUTH; pos <= EAST; pos++) {
        if ((pos == SOUTH) || (pos == NORTH)) {
            players[pos].cardAI = CARD_AI_STANDARD;
            players[pos].contractAI = CONTRACT_AI_STANDARD;
        }
        else {
            players[pos].cardAI = CARD_AI_FIRSTAVAILABLE;
            players[pos].contractAI = CONTRACT_AI_ALWAYSEIGHTY;
        }
        players[pos].pos = pos;
        players[pos].cards = playersCards[pos];
    }
    players[SOUTH].cardAI = CARD_USER;
    players[SOUTH].contractAI = CONTRACT_USER;
    for (Color color = SPADE; color <= CLUB; color++) {
        for (Value value = SEVEN; value <= ACE; value++) {
            players[0].cards[0].color = color;
            players[0].cards[0].value = value;
            displayCard(players[0].cards[0]);
            getchar();
            printf("\033[1A");
        }
    }
    
    
    printf("\033[4B");
    //playGame(players);
    /*averageGameLength = playAIGames(players, 1000, nbOfGamesWon);

    printf("Team SOUTH - NORTH won %d games!\n", nbOfGamesWon[0]);
    printf("Team  WEST - EAST  won %d games!\n", nbOfGamesWon[1]);
    printf("The games lasted %f rounds on average.\n", averageGameLength);
    */
    getchar();
    return EXIT_SUCCESS;
}