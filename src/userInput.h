#ifndef USERINPUT_H
#define USERINPUT_H
#include "core.h"

/* Asks the user to input a string
*   @param maxStrLength: the maximum length of the input string, including the terminating \0. Anything bigger than that will be cropped
*   @param displayStrline1[]: first line of the prompt given to the user asking for an input
*   @param displayStrline2[]: second line of the prompt given to the user. If useSecondLineAsInput is set to true, this is ignored
*   @param  useSecondLineAsInput: if set to TRUE, the user will input the string on an empty second line instead of the end of the current line
*   @return inputStr*: pointer to the first char of the user string. Must be freed eventually!
*/
char* inputUserStr(int maxStrLength, char displayStrline1[], char displayStrline2[], Bool useSecondLineAsInput);

/* Asks the user for an int between two bounds
*   @param minBound: the minimum valid value the user can enter
*   @param maxBound: the maximum valid value the user can enter
*   @param displayStr[]: the prompt given to the user asking for an input
*   @return userVal: the value entered by the user, guaranteed to be an int between minBound and maxBound
*/
int inputUserInt(int minBound, int maxBound, char displayStr[]);

/* Asks the user to press enter, and eventually display a message along with it
*   @param displayMsg[]: the optional message to display. To ignore this argument, set it to ""
*/
void inputUserAcknowledgement(char displayMsg[]);

/* Asks the user for a card to play among the valid ones, according to the Coinche rules
*   @param cardArray[]: array containing the player's cards
*   @param nbOfCards: the number of cards in cardArray
*/
Card askUserCard(Card cardArray[], int nbOfCards);

/* Asks the user for their action during their bidding turn, according to the Coinche rules
*   @param *contract: pointer to the contract being debated
*/
Bool askUserContract(Contract *contract);

#endif // USERINPUT_H
