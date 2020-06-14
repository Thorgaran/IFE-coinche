#ifndef USERINPUT_H
#define USERINPUT_H
#include "core.h"

/** 
 * \fn char* inputUserStr(int maxStrLength, char displayStrline1[], char displayStrline2[], Bool useSecondLineAsInput)
 * @param maxStrLength: the maximum length of the input string, including the terminating \0. Anything bigger than that will be cropped
 * @param displayStrline1[]: first line of the prompt given to the user asking for an input
 * @param displayStrline2[]: second line of the prompt given to the user. If useSecondLineAsInput is set to true, this is ignored
 * @param  useSecondLineAsInput: if set to TRUE, the user will input the string on an empty second line instead of the end of the current line
 * @return *inputStr: pointer to the first char of the user string. Must be freed eventually!
 * 
 * Asks the user to input a string
*/
char* inputUserStr(int maxStrLength, char displayStrline1[], char displayStrline2[], Bool useSecondLineAsInput);

/** 
 * \fn int inputUserInt(int minBound, int maxBound, char displayStr[])
 * @param minBound: the minimum valid value the user can enter
 * @param maxBound: the maximum valid value the user can enter
 * @param displayStr[]: the prompt given to the user asking for an input
 * @return userVal: the value entered by the user, guaranteed to be an int between minBound and maxBound
 * 
 * Asks the user for an int between two bounds
*/
int inputUserInt(int minBound, int maxBound, char displayStr[]);

/** 
 * \fn void inputUserAcknowledgement(char displayMsg[])
 * @param displayMsg[]: the optional message to display. To ignore this argument, set it to ""
 * 
 * Asks the user to press enter, and eventually display a message along with it
*/
void inputUserAcknowledgement(char displayMsg[]);

/** 
 * \fn char* inputUserName(char displayMsg[])
 * @param displayMsg[]: the prompt given to the user asking for a name
 * @return *userName: pointer to the first char of the user name. Must be freed eventually!
 * 
 * Asks the user to enter a player name. Prevent the user from entering ';' or any character not in the ASCII range 32-126
*/
char* inputUserName(char displayMsg[]);

/** 
 * \fn Card askUserCard(Card cardArray[], int nbOfCards)
 * @param cardArray[]: array containing the player's cards
 * @param nbOfCards: the number of cards in cardArray
 * 
 * Asks the user for a card to play among the valid ones, according to the Coinche rules
*/
Card askUserCard(Card cardArray[], int nbOfCards);

/** 
 * \fn Bool askUserContract(Contract *contract)
 * @param *contract: pointer to the contract being debated
 * 
 * Asks the user for their action during their bidding turn, according to the Coinche rules
*/
Bool askUserContract(Contract *contract);

#endif // USERINPUT_H
