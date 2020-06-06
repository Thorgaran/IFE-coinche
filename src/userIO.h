#ifndef USERIO_H
#define USERIO_H
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

Card askUserCard(Card cardArray[], int nbOfCards);

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract);

/* Takes a string and returns a cropped version of it with dots at the end if it exceeds a given length
*   @param string[]: the string to crop
*   @param maxLength: the maximum length the string can be without cropping
*   @return croppedString*: pointer to the first char of the cropped string. Must be freed eventually!
*/
char* cropStr(char string[], int maxLength);

/* Takes a string and returns a fixed length, text-aligned version of it, cropped and or underlined if needed
*   @param string[]: the string to center
*   @param maxLength: the maximum length of the space the centered string will be displayed in
*   @param textPosition: text alignement within the string (left, center, right)
*   @param underline: TRUE if the text sould be underlined, FALSE otherwise
*   @return formattedString*: pointer to the first char of the centered string. Must be freed eventually!
*/
char* formatStr(char string[], int maxLength, TextPosition textPosition, Bool underline);

/* Displays an empty card at the current cursor position (the cursor comes back to that position afterwards)
*/
void displayEmptyCard(void);

/* Deletes a card at the current cursor position (the cursor comes back to that position afterwards)
*/
void deleteCardDisplay(void);

/* Clears a card at the current cursor position (the cursor comes back to that position afterwards)
*/
void clearCardDisplay(void);

/* Changes a card at the current cursor position (the cursor comes back to that position afterwards)
*   @param card: the card to display. Only its value and color matter
*/
void changeCardDisplay(Card card);

/* Displays an empty play table
*/
void displayTable(void);

/* Clears the info box. The cursor is set to the middle of the first line
*/
void clearInfoMsg(void);

/* Displays a centered message in the info box. The cursor is left to the end of the message
*   @param messageLine1[]: the first line of the message to display
*   @param messageLine2[]: the second line of the message to display
*/
void displayInfoMsg(char messageLine1[], char messageLine2[]);

/* Clears top-right box. The cursor is left untouched
*/
void clearTopRightBox(void);

/* Displays an empty "Last trick" template in the top-right box. The cursor is left untouched
*/
void prepareLastTrickDisplay(void);

/* Clears contract display. The cursor is left untouched
*/
void clearContractDisplay(void);

/* Fills in the contract table corner with a given contract
*   @param playerName: the contract issuer's name
*   @param contract: the contract to display
*/
void updateContractDisplay(char playerName[], Contract contract);

/* Displays a centered, cropped player name at the right place on the table, optionnally underlined
*   @param player: the player whose name should be displayed
*   @param underline: TRUE if the name sould be underlined, FALSE otherwise
*/
void displayPlayerName(Player player, Bool underline);

/* Replaces the old displayed round value with a new one
*   @param roundNb: the current round number. This shouldn't be a three digits number
*/
void updateRoundNbDisplay(int roundNb);

/* Updates the trick number display
*   @param trickNb: the trick number from 1 to 8. 0 is a valid value meaning that the bidding phase is starting
*/
void updateTrickNbDisplay(int trickNb);

/* Updates the team score display
*   @param players[]: array of 4 players
*/
void updateTeamScore(Player players[]);

/* Updates the last trick display with new cards
*   @param lastTrickCards[]: 4-card array containing the previous trick cards
*   @param startingPlayer: position of the starting player of the previous trick
*/
void updateLastTrickDisplay(Card lastTrickCards[], Position startingPlayer);

/* Clears the 4 cards in the last trick display
*/
void clearLastTrickDisplay(void);

/* Displays a trick card in the middle of the table
*   @param playedCard: the card to display
*   @param currentPlayer: position of the player who just played the last card
*/
void displayTrickCard(Card playedCard, Position currentPlayer);

/* Deletes all 4 currently displayed trick cards
*/
void deleteDisplayedTrickCards(void);

/* Displays a line of sequencial numbers above the player's hand cards that can be played
*   @param cardInHand[]: array containing the player's cards (only the canPlay property is looked at)
*   @param nbOfCardsInHand: the number of cards in the SOUTH player's hand
*/
void displayNumbersAbovePlayerHand(Card cardsInHand[], int nbOfCardsInHand);

/* Displays the player's hand, centered
*   @param cardsInHand[]: array containing the player's cards
*   @param nbOfCardsInHand: the number of cards in cardsInHand
*/
void displayPlayerHand(Card cardsInHand[], int nbOfCardsInHand);

/* Deletes the content of the five lines (including the numbers line) containing the displayed player hand
*/
void deletePlayerHand(void);

/* Displays the current trick points of a player near its name 
*   @param points: the player's trick points
*   @param playerPos: the position the player
*/
void updatePlayerTrickPoints(int points, Position playerPos);

/* Clears all 4 displayed trick points
*/
void clearDisplayedTrickPoints(void);

/* Resizes the command prompt window to a given number of lines and columns
*   @param nbOfLines: the number of lines that should be displayed
*   @param nbOfColumns: the number of lines that should be displayed. Microsoft docs recommands a value between 40 and 135
*/
void resizeCmdWindow(int nbOfLines, int nbOfColumns);

#endif // USERIO_H