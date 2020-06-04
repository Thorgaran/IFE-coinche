#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userIO.h"
#include "ai.h" //TO DELETE

#define UNDERLINE_SEQUENCE_LENGTH 9

Card askUserCard(Card cardArray[], int nbOfCards) {
    displayNumbersAbovePlayerHand(nbOfCards);
    Card chosenCard = getAICardFirstAvailable(cardArray, nbOfCards);
    return chosenCard;
}

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract) {
    Bool hasPassed = TRUE;
    return hasPassed;
}

char* cropStr(char string[], int maxLength) {
    char* croppedString = (char*) malloc((maxLength + 3) * sizeof(char)); //Create the return pointer and allocate enough memory
    strncpy(croppedString, string, maxLength);  //Copy the input string into the output string (limited to maxLength)
    if (strlen(string) > maxLength) {           //If the input string is too long,
        croppedString[maxLength - 1] = '\0';    //put the terminating \0 in croppedString,
        strcat(croppedString, "…");             //and put dots at the end
    }
    else if (strlen(string) == maxLength) {
        croppedString[maxLength] = '\0'; //Put the terminating \0 in croppedString
    }
    return croppedString;
}

char* formatStr(char string[], int maxLength, TextPosition textPosition, Bool underline) {
    char* formattedString; //Create the return pointer
    char* croppedString = cropStr(string, maxLength); //Crop the input string if it's too long
    int additionalStrLength = 0, nbOfStartSpaces, nbOfEndSpaces, croppedStringLength = strlen(croppedString);
    if (croppedStringLength  < maxLength) { //Align the string if it's shorter than the maximum length
        formattedString = (char*) malloc((maxLength + 3 + UNDERLINE_SEQUENCE_LENGTH) * sizeof(char)); //Allocate memory for the return pointer
        switch (textPosition) { //Select the right number of spaces at the start and at the end depending on textPosition
            case TEXT_LEFT:
                nbOfStartSpaces = 0;
                nbOfEndSpaces = croppedStringLength;
                break;
            case TEXT_CENTER:
                nbOfStartSpaces = (maxLength - croppedStringLength)/2;
                nbOfEndSpaces = (maxLength + croppedStringLength)/2;
                break;
            case TEXT_RIGHT:
                nbOfStartSpaces = maxLength - croppedStringLength;
                nbOfEndSpaces = maxLength;
                break;
        }
        for(int i = 0; i < nbOfStartSpaces; i++) { //Put the right number of spaces at the start of formattedString
            formattedString[i] = ' ';
        }
        formattedString[nbOfStartSpaces] = '\0';    //Prepare formattedString for concatenation
        if (underline == TRUE) {                    //If underline mode,
            strcat(formattedString, "\033[4m");     //append opening underline sequence
            strcat(formattedString, croppedString); //Paste croppedString at the end of formattedString
            strcat(formattedString, "\033[24m");    //Append closing underline sequence
            additionalStrLength = UNDERLINE_SEQUENCE_LENGTH;
        }
        else {                                      //If not underline mode,
            strcat(formattedString, croppedString); //paste croppedString at the end of formattedString
        }
        free(croppedString); //CroppedString is not needed anymore, free it
        for(int i = nbOfEndSpaces + additionalStrLength; i < maxLength + additionalStrLength; i++) { //Put the right number of spaces at the end of formattedString
            formattedString[i] = ' ';
        }
        formattedString[maxLength + additionalStrLength] = '\0'; //Put the terminating \0
    }
    else {
        if (underline == TRUE) {                    //If underline mode,
            formattedString = (char*) malloc((maxLength + 3 + UNDERLINE_SEQUENCE_LENGTH) * sizeof(char)); //Allocate memory for the return pointer
            formattedString[0] = '\0';              //prepare formattedString for concatenation
            strcat(formattedString, "\033[4m");     //Append opening underline sequence
            strcat(formattedString, croppedString); //Paste croppedString at the end of formattedString
            strcat(formattedString, "\033[24m");    //Append closing underline sequence
            free(croppedString); //CroppedString is not needed anymore, free it
        }
        else {                                  //If not underline mode,
            formattedString = croppedString;    //formattedString is set to be the cropped string pointer
        }
    }
    return formattedString;
}

void displayEmptyCard(void) {
    printf("╭───╮\033[5D\033[1B");
    printf("│   │\033[5D\033[1B");
    printf("│   │\033[5D\033[1B");
    printf("╰───╯\033[5D\033[3A");
}

void deleteCardDisplay(void) {
    printf("     \033[5D\033[1B");
    printf("     \033[5D\033[1B");
    printf("     \033[5D\033[1B");
    printf("     \033[5D\033[3A");
}

void clearCardDisplay(void) {
    printf("\033[1C\033[1B  \033[1B \033[4D\033[2A"); //Clear the card content
}

void changeCardDisplay(Card card) {
    printf("\033[1C\033[1B%s\033[1B%s\033[4D\033[2A", VALUE_STR_TABLE[card.value], COLOR_STR_TABLE[card.color]);
    //Change the value, then the color, then return the cursor to the top-left of the card
}

void displayTable(void) {
    printf("╔═══════════════╤═════════════════════╤═══════════════╗\n");
    printf("║Contract:      │                     │  Last trick:  ║\n");
    printf("║               │     ╭┈┈┈┈┈┈┈┈┈╮     │               ║\n");
    printf("║               │     ┊ Round   ┊     │               ║\n");
    printf("║               │     ┊         ┊     │               ║\n");
    printf("╟───────┬───────┤     ╰┈┈┈┈┈┈┈┈┈╯     │               ║\n");
    printf("║Your   │Rival  │                     │               ║\n");
    printf("║team   │team   │                     │               ║\n");
    printf("║score: │score: │                     │               ║\n");
    printf("║  0/701│  0/701│                     │               ║\n");
    printf("╟───────┴───────╯                     ╰───────────────╢\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("║                      Your hand                      ║\n");
    printf("╚═════════════════════════════════════════════════════╝\n");
}

void clearTopRightBox(void) {
    printf("\033[s\033[2;40H"); //Save cursor position and move cursor to the top left of the top right box
    for (int i = 0; i < 9; i++) {
        printf("               \033[15D\033[1B"); //Clear line (inside the top right box), then move cursor to the next line
    }
    printf("\033[u"); //Restore cursor position
}

void prepareLastTrickDisplay(void) {
    clearTopRightBox(); //Needed to avoid having any leftover characters
    printf("\033[s\033[2;42HLast trick:\033[1B\033[8D");
    //Save cursor position, move cursor near the top left of the top right box, print "Last trick:", move cursor to the first card
    displayEmptyCard();
    printf("\033[2B\033[5D"); //Move cursor to the second card
    displayEmptyCard();
    printf("\033[10C"); //Move cursor to the third card
    displayEmptyCard();
    printf("\033[2B\033[5D"); //Move cursor to the fourth card
    displayEmptyCard();
    printf("\033[u"); //Restore cursor position
}

void clearContractDisplay(void) {
    printf("\033[s\033[3;2H"); //Save cursor position and move cursor to the contract corner
    for (int i = 0; i < 3; i++) {
        printf("               \033[1E\033[1C"); //Clear line (inside the contract box)
    }
    printf("\033[u"); //Restore cursor position
}

void updateContractDisplay(char playerName[], Contract contract) {
    char* shortName = cropStr(playerName, 15); //Get the player name cropped to 15 characters if needed
    clearContractDisplay(); //Clear contract display to avoid having leftover characters
    printf("\033[s\033[3;2H"); //Save cursor position and move cursor to the contract corner
    printf(shortName); //Print the contract issuer's name
    free(shortName); //Free the short name;
    printf("\033[1E\033[1C"); //Move cursor to the value and color field
    if (contract.type == POINTS) {      //If the contract is of type POINTS,
        printf("%d ", contract.points); //print the contract value
    }
    else {
        printf("%s ", CONTRACTTYPE_STR_TABLE[contract.type]); //Else, print the contract type string
    }
    printf("%s", COLOR_STR_TABLE[contract.trump]); //Then, print the color character
    printf("\033[1E\033[1C"); //Move cursor to the coinche field
    printf("%s", COINCHE_STR_TABLE[contract.coinche]); //Print the coinche state
    printf("\033[u"); //Restore cursor position
}

void displayPlayerName(Player player, Bool underline) {
    char* formattedPlayerName;
    printf("\033[s"); //Save cursor position
    switch (player.pos) { //More efficient than using arrays, given how much varies between the different player positions
        case SOUTH:
            printf("\033[18;2H"); //Move cursor to the player's display name location
            formattedPlayerName = formatStr(player.name, 53, TEXT_CENTER, underline); //Get the formatted name
            printf(formattedPlayerName); //Print the formatted name
            break;
        case WEST:
            printf("\033[13;2H"); //Move cursor to the player's display name location
            formattedPlayerName = formatStr(player.name, 17, TEXT_RIGHT, underline); //Get the formatted name
            printf(formattedPlayerName); //Print the formatted name
            break;
        case NORTH:
            printf("\033[9;18H"); //Move cursor to the player's display name location
            formattedPlayerName = formatStr(player.name, 21, TEXT_CENTER, underline); //Get the formatted name
            printf(formattedPlayerName); //Print the formatted name
            break;
        case EAST:
            printf("\033[13;38H"); //Move cursor to the player's display name location
            formattedPlayerName = formatStr(player.name, 17, TEXT_LEFT, underline); //Get the formatted name
            printf(formattedPlayerName); //Print the formatted name
            break;
    }
    free(formattedPlayerName); //Free the pointer after its use
    printf("\033[u"); //Restore cursor position
}

void updateRoundNbDisplay(int roundNb) {
    printf("\033[s\033[4;31H  \033[2D%d\033[u", roundNb);
    //Save cursor position, move it to the round number, clear it, move back to the round number, display the new one, restore cursor position
}

void updateTrickNbDisplay(int trickNb) {
    printf("\033[s"); //Save cursor position
    switch (trickNb) {
        case 0:                             //If the bidding phase is starting,
            printf("\033[5;24H Bidding ");  //go to the second line of the round display and write " Bidding "
            break;
        case 1:                             //If this is the first trick of the round,
            printf("\033[5;24HTrick 1/8");  //go to the second line of the round display and replace " Bidding " with this
            break;
        default:
            printf("\033[5;30H%d", trickNb); //Else, go to the trick number display and update the value
            break;
    }
    printf("\033[u"); //Restore cursor position
}

void updateTeamScore(Player players[]) {
    char* formattedScore;
    char teamScoreStr[5];
    sprintf(teamScoreStr, "%d", players[SOUTH].teamScore);          //Store the user team's score in a string
    formattedScore = formatStr(teamScoreStr, 3, TEXT_RIGHT, FALSE); //Format this score string
    printf("\033[s\033[10;2H%s", formattedScore);                   //Save cursor position, move cursor to the user team's score display, display formatted score
    free(formattedScore);                                           //Free the user team's formatted score since it's not needed anymore
    sprintf(teamScoreStr, "%d", players[EAST].teamScore);           //Store the user rival team's score in a string
    formattedScore = formatStr(teamScoreStr, 3, TEXT_RIGHT, FALSE); //Format this score string
    printf("\033[5C%s", formattedScore);                            //Move cursor to the user rival team's score display, display formatted score
    free(formattedScore);                                           //Free the user rival team's formatted score since it's not needed anymore
    printf("\033[u");                                               //Restore cursor position
}

void updateLastTrickDisplay(Card lastTrickCards[], Position startingPlayer) {
    printf("\033[s\033[7;45H"); //Save cursor position, and move cursor to the SOUTH card in the last trick display
    changeCardDisplay(lastTrickCards[(4 - startingPlayer)%4]);
    printf("\033[5D\033[2A"); //Move cursor to the WEST card
    changeCardDisplay(lastTrickCards[(5 - startingPlayer)%4]);
    printf("\033[5C\033[2A"); //Move cursor to the NORTH card
    changeCardDisplay(lastTrickCards[(6 - startingPlayer)%4]);
    printf("\033[2B\033[5C"); //Move cursor to the EAST card
    changeCardDisplay(lastTrickCards[3 - startingPlayer]);
    printf("\033[u"); //Restore cursor position
}

void clearLastTrickDisplay(void) {
    printf("\033[s\033[7;45H"); //Save cursor position, and move cursor to the SOUTH card in the last trick display
    clearCardDisplay();
    printf("\033[5D\033[2A"); //Move cursor to the WEST card
    clearCardDisplay();
    printf("\033[5C\033[2A"); //Move cursor to the NORTH card
    clearCardDisplay();
    printf("\033[2B\033[5C"); //Move cursor to the EAST card
    clearCardDisplay();
    printf("\033[u"); //Restore cursor position
}

void displayTrickCard(Card playedCard, Position currentPlayer) {
    printf("\033[s"); //Save cursor position
    switch (currentPlayer) {
        case SOUTH:
            printf("\033[14;26H"); //Move cursor to the SOUTH trick card location
            displayEmptyCard();
            changeCardDisplay(playedCard);
            break;
        case WEST:
            printf("\033[12;20H"); //Move cursor to the WEST trick card location
            displayEmptyCard();
            changeCardDisplay(playedCard);
            break;
        case NORTH:
            printf("\033[10;26H"); //Move cursor to the NORTH trick card location
            displayEmptyCard();
            changeCardDisplay(playedCard);
            break;
        case EAST:
            printf("\033[12;32H"); //Move cursor to the EAST trick card location
            displayEmptyCard();
            changeCardDisplay(playedCard);
            break;
    }
    printf("\033[u"); //Restore cursor position
}

void deleteDisplayedTrickCards(void) {
    printf("\033[s\033[14;26H"); //Save cursor position, and move cursor to the SOUTH trick card location
    deleteCardDisplay();
    printf("\033[12;20H"); //Move cursor to the WEST trick card location
    deleteCardDisplay();
    printf("\033[10;26H"); //Move cursor to the NORTH trick card location
    deleteCardDisplay();
    printf("\033[12;32H"); //Move cursor to the EAST trick card location
    deleteCardDisplay();
    printf("\033[u"); //Restore cursor position
}

void displayNumbersAbovePlayerHand(int nbOfCardsInHand) {
    printf("\033[s\033[21;%dH", 7 + 3 * (8 - nbOfCardsInHand));
    //Save cursor position, and move cursor to the leftmost position of the player's hand on the numbers line, depending on the number of cards to display
    for (int i = 1; i <= nbOfCardsInHand; i++) {    //For each card in hand,
        printf("%d\033[5C", i);                     //display a number above it
    }
    printf("\033[u"); //Restore cursor position
}

void displayPlayerHand(Card cardsInHand[], int nbOfCardsInHand) {
    deletePlayerHand(); //Needed to avoid having leftover characters from the previous hand
    printf("\033[s\033[22;%dH", 5 + 3 * (8 - nbOfCardsInHand));
    //Save cursor position, and move cursor to the leftmost position of the player's hand, depending on the number of cards to display
    for (int i = 1; i <= nbOfCardsInHand; i++) {
        displayEmptyCard();
        changeCardDisplay(cardsInHand[i-1]);
        printf("\033[6C"); //Move cursor over to the next card
    }
    printf("\033[u"); //Restore cursor position
}

void deletePlayerHand(void) {
    printf("\033[s\033[21;5H"); //Save cursor position, and move cursor to the leftmost position of the player's hand (on the line with the numbers)
    for (int i = 0; i < 5; i++) { //Five iterations because the line with the numbers must be deleted as well
        printf("                                               \033[47D\033[1B"); //Clear the line and move to beginning of the next line
    }
    printf("\033[u"); //Restore cursor position
}

void updatePlayerTrickPoints(int points, Position playerPos) {
    char* formattedTrickPoints;
    char playerTrickPointsStr[4];
    printf("\033[s"); //Save cursor position
    sprintf(playerTrickPointsStr, "%d", points); //Store the player's trick points in a string
    switch (playerPos) {
        case SOUTH:
            formattedTrickPoints = formatStr(playerTrickPointsStr, 3, TEXT_CENTER, FALSE); //Format the trick points string with centered text
            printf("\033[19;27H%s", formattedTrickPoints); //Move cursor to the SOUTH player's trick points and print the points
            break;
        case WEST:
            formattedTrickPoints = formatStr(playerTrickPointsStr, 3, TEXT_RIGHT, FALSE); //Format the trick points string with right text
            printf("\033[14;16H%s", formattedTrickPoints); //Move cursor to the WEST player's trick points and print the points
            break;
        case NORTH:
            formattedTrickPoints = formatStr(playerTrickPointsStr, 3, TEXT_CENTER, FALSE); //Format the trick points string with centered text
            printf("\033[8;27H%s", formattedTrickPoints); //Move cursor to the NORTH player's trick points and print the points
            break;
        case EAST:
            formattedTrickPoints = formatStr(playerTrickPointsStr, 3, TEXT_LEFT, FALSE); //Format the trick points string with left text
            printf("\033[14;38H%s", formattedTrickPoints); //Move cursor to the EAST player's trick points and print the points
            break;
    }
    free(formattedTrickPoints); //Free formattedTrickPoints as it's not needed anymore
    printf("\033[u"); //Restore cursor position
}

void clearDisplayedTrickPoints(void) {
    printf("\033[s\033[19;27H   \033[14D\033[5A   \033[6A\033[8C   \033[8C\033[6B   \033[u");
    //Save cursor position, move to each player's displayed trick points in clockwise order starting with the SOUTH player then clear it, restore cursor position
}