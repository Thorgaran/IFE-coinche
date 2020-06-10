#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "userInput.h"
#include "displayMain.h"
#include "displayRound.h"

char* inputUserStr(int maxStrLength, char displayStrline1[], char displayStrline2[], Bool useSecondLineAsInput) {
    char c;
    char* inputStr = NULL;
    char* fgetsReturnPtr = NULL;
    int inputStrLength;
    inputStr = (char*) malloc(maxStrLength);    //Allocate enough memory for the input string
    if (useSecondLineAsInput) {                 //If using the second line as input,
        displayInfoMsg(displayStrline1, "");    //Display only on the first line
        printf("\033[1E\033[2C");               //Move cursor to the next line to have more room to write the string
    }
    else {
        displayInfoMsg(displayStrline1, displayStrline2); //Else, display on both lines
    }
    fgetsReturnPtr = fgets(inputStr, maxStrLength, stdin); //Ask user for a string
    while (fgetsReturnPtr == NULL) {
        if (useSecondLineAsInput) {     //If using the second line as input
            displayInfoMsg("Couldn't read the input string. Please try again.", ""); //Display an error message on the first line only
            printf("\033[1E\033[2C");   //Move cursor to the next line to have more room to write the string
        }
        else {
            displayInfoMsg("Couldn't read the input string. Please try again.", displayStrline1); //Else, display things on both lines
        }
        fgetsReturnPtr = fgets(inputStr, maxStrLength, stdin); //Ask user for a string
    }
    inputStrLength = strlen(inputStr);  //This will be used multiple times
    c = inputStr[inputStrLength-1];     //Store the last char of the string in c
    while ((c != '\n') && (c != EOF)) {
        c = getchar();                  //Flush leftover input
    }
    if (inputStr[inputStrLength-1] == '\n') {   //If there's an \n at the end of the string,
        inputStr[inputStrLength-1] = '\0';      //remove it
    }
    clearInfoMsg();
    return inputStr;
}

int inputUserInt(int minBound, int maxBound, char displayStr[]) {
    char formattedErrorMsg[30];
    char* inputStr = NULL;
    char* endPtr = NULL;
    int userVal = __INT_MAX__;
    long userValLong;
    inputStr = inputUserStr(5, displayStr, "", FALSE); //Ask the user for an input
    userValLong = strtol(inputStr, &endPtr, 10); //Try to convert the string to a long
    while ((endPtr == inputStr) || (userValLong < minBound) || (userValLong > maxBound)) { //The condition order is very important!
        //While the address pointed to by endPtr is the first one of the inputStr (so if reading a long was unsuccessful), or the value is not between the bounds
        sprintf(formattedErrorMsg, "'%s' is not a valid input.", inputStr); //Construct the error message. inputStr is guaranteed to be 5 chars or less
        free(inputStr); //Free the last input, as it's a bad input that can be deleted safely
        inputStr = inputUserStr(5, formattedErrorMsg, displayStr, FALSE); //Ask the user for an input
        userValLong = strtol(inputStr, &endPtr, 10); //Try to convert the string to a long
    };
    free(inputStr); //Free the last input, as it's already converted to an int
    userVal = userValLong;
    clearInfoMsg();
    return userVal;
}

void inputUserAcknowledgement(char displayMsg[]) {
    printf("\033[?25l"); //Hide cursor
    if (displayMsg[0] == '\0') { //If there is no message to display
        free(inputUserStr(2, "Press enter to continue.", "", FALSE)); //The input string pointer, not needed, is immediately freed
    }
    else {
        free(inputUserStr(2, displayMsg, "Press enter to continue.", FALSE)); //The input string pointer, not needed, is immediately freed
    }
    printf("\033[?25h"); //Show cursor
}

Card askUserCard(Card cardArray[], int nbOfCards) {
    Card chosenCard;
    int chosenCardID;
    displayNumbersAbovePlayerHand(cardArray, nbOfCards); //Display numbers only above playable cards
    chosenCardID = inputUserInt(1, nbOfCards, "Play a card: enter the card's displayed number "); //Ask the user to choose a card
    while (cardArray[chosenCardID-1].canPlay == FALSE) { //While the user selects a wrong card
        chosenCardID = inputUserInt(1, nbOfCards, "You can't play this card. Choose another one "); //Ask the user again to choose a card
    }
    chosenCard = cardArray[chosenCardID-1]; //Get the chosen card from the player's hand
    return chosenCard;
}

Bool askUserContract(Contract *contract) {
    Bool hasPassed = TRUE, secondMenuOptionIsBid = TRUE;
    int chosenMenuOption, numberOfMenuOptions = 1, minContractPoints = (contract->points == 0) ? 80 : contract->points + 10; //Ternary to make a more concise code
    char lineToDisplay[53];
    displayBiddingMenuLine("Bidding options", TRUE, FALSE);
    displayBiddingMenuLine("1: Pass", FALSE, FALSE); //The player can always decide to pass
    if ((contract->coinche == NOT_COINCHED) && (contract->type != GENERAL)) { //If the contract isn't coinched and isn't a General
        displayBiddingMenuLine("2: Bid", FALSE, FALSE); //The player has the option to bid
        numberOfMenuOptions++; //Increase the number of menu options
    }
    else {
        secondMenuOptionIsBid = FALSE; //No bidding option for the user
    }
    if ((contract->coinche == NOT_COINCHED) && (contract->points != 0) && (contract->issuer != NORTH)) {
    //If the contract isn't coinched, AND someone made a contract already, AND the partner isn't the contract issuer. The condition order is important
        sprintf(lineToDisplay, "%d: Coinche", numberOfMenuOptions+1); //Prepare the line to display
        displayBiddingMenuLine(lineToDisplay, FALSE, FALSE); //The player can coinche
        numberOfMenuOptions++; //Increase the number of menu options
    }
    else if ((contract->coinche == COINCHED) && ((contract->issuer == SOUTH) || (contract->issuer == NORTH))) {
    //If the contract is coinched, AND the contract issuer is of the player's team
        sprintf(lineToDisplay, "%d: Overcoinche", numberOfMenuOptions+1); //Prepare the line to display
        displayBiddingMenuLine(lineToDisplay, FALSE, FALSE); //The player can overcoinche
        numberOfMenuOptions++; //Increase the number of menu options
    }
    displayBiddingMenuLine("", FALSE, TRUE); //Stop displaying lines for this menu
    chosenMenuOption = inputUserInt(1, numberOfMenuOptions, "Bidding: enter an available action number "); //Ask the user to decide what to do
    if (chosenMenuOption != 1) { //If the player didn't pass
        hasPassed = FALSE;
        if (secondMenuOptionIsBid && (chosenMenuOption == 2)) { //If the player decided to bid
            displayBiddingMenuLine(" Trump options", TRUE, FALSE);
            displayBiddingMenuLine("1: Spade", FALSE, FALSE);
            displayBiddingMenuLine("2: Heart", FALSE, FALSE);
            displayBiddingMenuLine("3: Diamond", FALSE, FALSE);
            displayBiddingMenuLine("4: Club", FALSE, FALSE);
            displayBiddingMenuLine("5: All trump", FALSE, FALSE);
            displayBiddingMenuLine("6: No trump", FALSE, TRUE);
            chosenMenuOption = inputUserInt(1, 6, "Select a trump: enter its number "); //Ask the user to choose a trump
            contract->trump = chosenMenuOption; //Change the contract's trump
            displayBiddingMenuLine(" Value options", TRUE, FALSE);
            if (contract->points < 160) { //If the contract has a point value inferior to 160 (thus it's also not a Capot or a General)
                sprintf(lineToDisplay, "1: Points(%d%s)", minContractPoints, (contract->points == 150) ? "" : "+");
                //Prepare the line to display. Using the ternary operator here to make it more concise
                displayBiddingMenuLine(lineToDisplay, FALSE, FALSE);
                displayBiddingMenuLine("2: Capot", FALSE, FALSE);
                displayBiddingMenuLine("3: General", FALSE, TRUE);
                numberOfMenuOptions = 3;
            }
            else if (contract->points == 160) { //If the contract has a point value of 160
                displayBiddingMenuLine("1: Capot", FALSE, FALSE);
                displayBiddingMenuLine("2: General", FALSE, TRUE);
                numberOfMenuOptions = 2;
            }
            else { //The contract is a Capot
                displayBiddingMenuLine("1: General", FALSE, TRUE);
                numberOfMenuOptions = 1;
            }
            chosenMenuOption = inputUserInt(1, numberOfMenuOptions, "Select a value: enter the corresponding number "); //Ask the user to select the contract value
            if (chosenMenuOption == numberOfMenuOptions) { //If the user selected General
                contract->type = GENERAL;
                contract->points = 500;
            }
            else if (chosenMenuOption == numberOfMenuOptions - 1) { //If the user selected Capot
                contract->type = CAPOT;
                contract->points = 250;
            }
            else { //If the user selected points
                sprintf(lineToDisplay, "Enter the desired points between %d and 160 ", minContractPoints); //Prepare the line to display
                contract->points = inputUserInt(minContractPoints, 160, lineToDisplay); //Ask the user for the desired contract points
                while (contract->points % 10 != 0) { //While the selected value isn't a multiple of 10
                    contract->points = inputUserInt(minContractPoints, 160, "This isn't divisible by 10. Please try again "); //Ask the user again for the desired contract points
                }
            }
        }
        else { //The player decided to coinche or overcoinche
            contract->coinche++; //Set the contract to COINCHED or OVERCOINCHED depending on its previous state
        }
    }
    clearTopRightBox();
    return hasPassed;
}