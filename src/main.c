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
    /*

    printf("Team SOUTH - NORTH won %d games!\n", nbOfGamesWon[0]);
    printf("Team  WEST - EAST  won %d games!\n", nbOfGamesWon[1]);
    printf("The games lasted %f rounds on average.\n", averageGameLength);
    */
    tearDown(players);
    return EXIT_SUCCESS;
}

void mainMenu(Player players[]) {
    char *inputStr = NULL;
    char message[54];
    float averageGameLength;
    int nbOfAIGames, nbOfGamesWon[2];
    CardAI southCardAI;
    ContractAI southContractAI;
    Bool exitProgram = FALSE;
    while (exitProgram == FALSE) {
        displayMenu();
        int chosenMenuOption = inputUserInt(1, 6, "Select a menu item: enter its number ");
        switch (chosenMenuOption) {
            case 1:
                southCardAI = players[SOUTH].cardAI; //Save the south player AIs
                southContractAI = players[SOUTH].contractAI;
                players[SOUTH].cardAI = CARD_USER; //Set the south player AIs to be a user
                players[SOUTH].contractAI = CONTRACT_USER;
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
                players[SOUTH].cardAI = southCardAI; //Restore the south player AIs
                players[SOUTH].contractAI = southContractAI;
                break;
            case 2:
                inputStr = inputUserStr(2, "Do you want to change AI types? [Y/n] ", "", FALSE);
                if (inputStr[0] != 'n') { //If the player wants to change AI types
                    changePlayerSettings(players, "Continue");
                }
                free(inputStr); //Input string not needed anymore
                nbOfAIGames = inputUserInt(1, 10000, "Enter the number of games (1 - 10 000) ");
                nbOfGamesWon[0] = 0; //Reset the number of games won
                nbOfGamesWon[1] = 0;
                averageGameLength = playAIGames(players, nbOfAIGames, nbOfGamesWon);
                sprintf(message, "N-S %.2f%% wins, E-W %.2f%% wins, %.4f rounds avg", 100*nbOfGamesWon[0]/(float)nbOfAIGames, 100*nbOfGamesWon[1]/(float)nbOfAIGames, averageGameLength);
                //Prepare the results message and compute percentages
                inputUserAcknowledgement(message);
                break;
            case 3:
                changePlayerSettings(players, "Exit to menu");
                break;
            case 4: 
                displayLeaderboard();
                inputUserAcknowledgement("");
                break;
            case 5: 
                displayCredits();
                inputUserAcknowledgement("");
                break;
            case 6:
                exitProgram = TRUE;
                break;
        }
    }    
}

void changePlayerSettings(Player players[], char quitMsg[]) {
    char *formattedStr = NULL;
    char message[53];
    int chosenOption, nbOfIterations;
    Bool quit = FALSE, changeCardAI;
    while (quit == FALSE)
    {
        displayFrame();
        formattedStr = formatStr("Current AI settings:", 53, TEXT_CENTER, TRUE);
        printf("\033[3;2H%s\033[1E", formattedStr); //Move cursor to the third line, display the message, move cursor a line down
        free(formattedStr); //Free formattedStr, not needed anymore
        for (int i = 0; i < 4; i++) {
            sprintf(message, "%d: Name - %s", (3*i)+1, players[i].croppedName); //Prepare the name option
            printf("\033[1E\033[2C%s", message); //Move cursor one line down, and display the option
            sprintf(message, "%d: Card AI - %s", (3*i)+2, CARDAI_STR_TABLE[players[i].cardAI]); //Prepare the card AI option
            printf("\033[1E\033[2C%s", message); //Move cursor one line down, and display the option
            sprintf(message, "%d: Contract AI - %s", 3*(i+1), CONTRACTAI_STR_TABLE[players[i].contractAI]); //Prepare the contract AI option
            printf("\033[1E\033[2C%s\033[1E", message); //Move cursor one line down, display the option, move cursor a line down
        }
        printf("\033[1E\033[2C13: %s", quitMsg); //Move cursor a line down, display the quit option
        chosenOption = inputUserInt(1, 13, "Select a setting to edit (enter its number) "); //Ask the user to select a setting to change
        if (chosenOption == 13) { //If the user wants to quit
            quit = TRUE;
        }
        else if (chosenOption%3 == 1) { //If the user wants to change an AI name
            free(players[chosenOption/3].name); //Free the previous name
            free(players[chosenOption/3].croppedName); //Free the previous cropped name
            players[chosenOption/3].name = inputUserName("Enter the new name (50 characters max)");
            players[chosenOption/3].croppedName = cropStr(players[chosenOption/3].name, 15);
        }
        else { //If the user wants to change an AI type
            if (chosenOption%3 == 2) { //If the user wants to change a card AI
                nbOfIterations = NB_CARD_AI;
                changeCardAI = TRUE;
            }
            else { //If the user wants to change a contract AI
                nbOfIterations = NB_CONTRACT_AI;
                changeCardAI = FALSE;
            }
            displayFrame();
            sprintf(message, "Available %s AIs:", changeCardAI ? "card" : "contract"); //Prepare message (using ternary operator because it's more efficient)
            formattedStr = formatStr(message, 53, TEXT_CENTER, TRUE);
            printf("\033[3;2H%s\033[1E", formattedStr); //Move cursor to the third line, display the message, move cursor a line down
            free(formattedStr); //Free formattedStr, not needed anymore
            for (int i = 1; i < nbOfIterations; i++) {
                sprintf(message, "%d: %s", i, changeCardAI ? CARDAI_STR_TABLE[i] : CONTRACTAI_STR_TABLE[i]);
                //Prepare the AI type to display. The ternary operator makes a more concise code
                formattedStr = formatStr(message, 53, TEXT_CENTER, FALSE); //Center the message
                printf("\033[1E\033[1C%s", formattedStr); //Move cursor one line down, and display the AI type option
                free(formattedStr); //Free formattedStr, not needed anymore
            }
            sprintf(message, "Select a %s AI for %s ", changeCardAI ? "card" : "contract", players[(chosenOption-1)/3].croppedName); //Prepare prompt message
            if (changeCardAI) {
                players[(chosenOption-1)/3].cardAI = inputUserInt(1, NB_CARD_AI, message); //Ask the user to change the card AI
            }
            else {
                players[(chosenOption-1)/3].contractAI = inputUserInt(1, NB_CONTRACT_AI, message); //Ask the user to change the contract AI
            }
        }
    }
}

void setUp(Player players[]) {
    char *namePtrs[] = {NULL, NULL, NULL, NULL}, *croppedNamePtrs[] = {NULL, NULL, NULL, NULL};
    char defaultAINames[][9] = {"AI-West", "AI-North", "AI-East"};
    Card *playerCardsPtrs[] = {NULL, NULL, NULL, NULL};
    srand(time(0)); //Initialize the random function
    printf("\033[?1049h"); //Enable alternate screen buffer
    resizeCmdWindow(31, 55);
    displayFrame();
    for (Position pos = SOUTH; pos <= EAST; pos++) {
        players[pos].cardAI = CARD_AI_STANDARD; //Initialize the player card AI
        players[pos].contractAI = CONTRACT_AI_STANDARD; //Initialize the player contract AI
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