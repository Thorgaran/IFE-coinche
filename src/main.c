#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "play.h"
#include "displayMain.h"
#include "userInput.h"
#include "leaderboard.h"
#include "stringUtils.h"

int main (int argc, char* argv[]) {
    Player players[4];
    setUp(players);
    mainMenu(players);
    /*averageGameLength = playAIGames(players, 1000, nbOfGamesWon);

    printf("Team SOUTH - NORTH won %d games!\n", nbOfGamesWon[0]);
    printf("Team  WEST - EAST  won %d games!\n", nbOfGamesWon[1]);
    printf("The games lasted %f rounds on average.\n", averageGameLength);
    */
    tearDown(players);
    return EXIT_SUCCESS;
}

void mainMenu(Player players[]) {
    char *inputStr = NULL;
    //float averageGameLength;
    //int nbOfGamesWon[] = {0, 0};
    Bool exitProgram = FALSE;
    while (exitProgram == FALSE) {
        displayMenu();
        int chosenMenuOption = inputUserInt(1,4,"Select a menu item: enter its number ");
        switch (chosenMenuOption) {
            case 1:
                if (players[SOUTH].name == NULL) { //If the player doesn't have a name yet
                    players[SOUTH].name = inputUserName("Please enter your name (50 characters max)");
                    players[SOUTH].croppedName = cropStr(players[SOUTH].name, 15);
                }
                else { //If the player already has a name
                    inputStr = inputUserStr(2, players[SOUTH].name, "Do you want to change your name? [y/N] ", FALSE);
                    if (inputStr[0] == 'y') { //If the player wants to change name
                        free(players[SOUTH].name); //Free the previous name
                        free(players[SOUTH].croppedName); //Free the previous cropped name
                        players[SOUTH].name = inputUserName("Please enter your name (50 characters max)");
                        players[SOUTH].croppedName = cropStr(players[SOUTH].name, 15);
                    }
                    free(inputStr); //Input string not needed anymore
                }
                displayFrame();
                playGame(players);
                if (players[SOUTH].teamScore > 700) {   //If the user's team won,
                    increaseWins(players[SOUTH].name);  //increase the user's stored number of wins
                    inputUserAcknowledgement("          \033[0;32mYour team won! Congratulations!\033[0m"); //Display in green
                }
                else { //If the rival team won
                    inputUserAcknowledgement("         \033[0;31mYour team lost. Maybe next time!\033[0m"); //Display in red
                }
                break;
            case 2: 
                displayLeaderboard();
                inputUserAcknowledgement("");
                break;
            case 3: 
                //displayCredits();
                break;
            case 4:
                exitProgram = TRUE;
                break;
        }
    }    
}

void setUp(Player players[]) {
    char *namePtrs[] = {NULL, NULL, NULL, NULL}, *croppedNamePtrs[] = {NULL, NULL, NULL, NULL};
    char defaultAINames[][9] = {"AI-West", "AI-North", "AI-East"};
    Card *playerCardsPtrs[] = {NULL, NULL, NULL, NULL};
    CardAI defaultCardAI[] = {CARD_USER, CARD_AI_STANDARD, CARD_AI_STANDARD, CARD_AI_STANDARD};
    ContractAI defaultContractAI[] = {CONTRACT_USER, CONTRACT_AI_STANDARD, CONTRACT_AI_STANDARD, CONTRACT_AI_STANDARD,};
    srand(time(0)); //Initialize the random function
    printf("\033[?1049h"); //Enable alternate screen buffer
    resizeCmdWindow(31, 55);
    displayFrame();
    for (Position pos = SOUTH; pos <= EAST; pos++) {
        players[pos].cardAI = defaultCardAI[pos]; //Initialize the player card AI
        players[pos].contractAI = defaultContractAI[pos]; //Initialize the player contract AI
        players[pos].pos = pos; //Initialize the player position
        if (pos == SOUTH) { //No name initialization for the SOUTH player
            players[pos].name = namePtrs[pos];
            players[pos].croppedName = croppedNamePtrs[pos];
        }
        else {
            namePtrs[pos] = (char*) malloc(9 * sizeof(char)); //Allocate memory for the AI name
            players[pos].name = namePtrs[pos];
            croppedNamePtrs[pos] = (char*) malloc(9 * sizeof(char)); //Allocate memory for the AI cropped name
            players[pos].croppedName = croppedNamePtrs[pos];
            strcpy(players[pos].name, defaultAINames[pos-1]);           //Initialize the AI default name
            strcpy(players[pos].croppedName, defaultAINames[pos-1]);    //Initialize the AI default cropped name
        }
        playerCardsPtrs[pos] = (Card*) malloc(8 * sizeof(Card)); //Allocate memory for the player cards
        players[pos].cards = playerCardsPtrs[pos];
    }
}

void tearDown(Player players[]) {
    for (Position pos = SOUTH; pos <= EAST; pos++) {
        free(players[pos].name);
        free(players[pos].croppedName);
        free(players[pos].cards);
    }
    printf("\033[?1049l"); //Return to main screen buffer
}