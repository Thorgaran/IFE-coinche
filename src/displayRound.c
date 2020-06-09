#include <stdio.h>
#include <stdlib.h>
#include "displayRound.h"
#include "stringUtils.h"

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
    printf("\033[1C\033[1B  \033[1B \033[4D\033[2A"); //Clear the card content and return cursor to the top-left of the card
}

void changeCardDisplay(Card card) {
    printf("\033[1C\033[1B"); //Move cursor to the card displayed value
    if ((card.color == HEART) || (card.color == DIAMOND)) {
        printf("\033[0;31m%s\033[0m", VALUE_STR_TABLE[card.value][0]); //Display the value in red
    }
    else {
        printf("%s", VALUE_STR_TABLE[card.value][0]); //Display the value in the standard color
    }
    printf("\033[1B%s\033[4D\033[2A", COLOR_STR_TABLE[card.color]); //Display the color, then return the cursor to the top-left of the card
}

void displayTable(void) {
    printf("╔═══════════════╤═════════════════════╤═══════════════╗\n");
    printf("║Contract:      │                     │               ║\n");
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
    printf("╠═════════════════════════════════════════════════════╣\n");
    printf("║                                                     ║\n");
    printf("║                                                     ║\n");
    printf("╚═════════════════════════════════════════════════════╝");
    printf("\033[28;28H"); //Move cursor to the info box
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

void displayBiddingMenuLine(char lineToDisplay[], Bool firstLine, Bool lastLine) {
    if (firstLine) {
        clearTopRightBox();
        printf("\033[s\033[2;40H"); //Save cursor position and move cursor to the top left of the top right box
    }
    printf("%s\033[1E\033[39C", lineToDisplay); //Display the line and move over to the next line
    if (firstLine) {
        printf("\033[1E\033[39C"); //Skip a line to make the menu look nicer
    }
    if (lastLine) {
        printf("\033[u"); //Restore cursor position
    }
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
    char* croppedColor = NULL;
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
    if ((contract.type == GENERAL) && (contract.trump >= ALLTRUMP)) {   //If in this very special case (General + All or No trump),
        croppedColor = cropStr(COLOR_STR_TABLE[contract.trump], 7);     //shorten the color to fit in the contract box
        printf("%s", croppedColor); //Then, print the color character
        free(croppedColor); //Free croppedColor as it's not needed anymore
    }
    else {
        printf("%s", COLOR_STR_TABLE[contract.trump]); //Print the color character
    }
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

void displayNumbersAbovePlayerHand(Card cardsInHand[], int nbOfCardsInHand) {
    printf("\033[s\033[21;%dH", 7 + 3 * (8 - nbOfCardsInHand));
    //Save cursor position, and move cursor to the leftmost position of the player's hand on the numbers line, depending on the number of cards to display
    for (int i = 1; i <= nbOfCardsInHand; i++) {    //For each card in hand
        if (cardsInHand[i-1].canPlay == TRUE) {     //If the card can be played,
            printf("%d\033[5C", i);                 //display a number above the card
        }
        else {
            printf("\033[6C");                      //Else, move the cursor above the next card
        }
        
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