#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"
#include "play.h"
#include "displayMain.h"
#include "leaderboard.h"

int main (int argc, char* argv[]) {
    srand(time(0)); //Initialize the random function
    printf("\033[?1049h"); //Enable alternate screen buffer
    resizeCmdWindow(31, 55);
    /*float averageGameLength;
    int nbOfGamesWon[] = {0, 0};*/
    Card playersCards[4][8];
    char playerNames[4][MAX_PLAYER_NAME_LENGTH] = 
        {"Player",
         "AI-West",
         "AI-North",
         "AI-East"};
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
        players[pos].name = playerNames[pos];
    }

    players[SOUTH].cardAI = CARD_USER;
    players[SOUTH].contractAI = CONTRACT_USER;
    
    increaseWins(players[SOUTH].name);
    getchar();

    playGame(players);
    /*averageGameLength = playAIGames(players, 1000, nbOfGamesWon);

    printf("Team SOUTH - NORTH won %d games!\n", nbOfGamesWon[0]);
    printf("Team  WEST - EAST  won %d games!\n", nbOfGamesWon[1]);
    printf("The games lasted %f rounds on average.\n", averageGameLength);
    */

    for (Position pos = SOUTH; pos <= EAST; pos++) {
        free(players[pos].croppedName);
    }

    getchar();
    printf("\033[?1049l"); //Return to main screen buffer
    return EXIT_SUCCESS;
}