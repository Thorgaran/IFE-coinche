#ifndef USERIO_H
#define USERIO_H
#include "core.h"

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
void displayTable();

/* Clear contract display. The cursor is left untouched
*/
void clearContractDisplay(void);

/* Fill in the contract table corner with a given contract
*   @param playerName: the contract issuer's name
*   @param contract: the contract to display
*/
void updateContractDisplay(char playerName[], Contract contract);

/* Display a centered, cropped player name at the right place on the table, optionnally underlined
*   @param player: the player whose name should be displayed
*   @param underline: TRUE if the name sould be underlined, FALSE otherwise
*/
void displayPlayerName(Player player, Bool underline);

/* Replace the old displayed round value with a new one
*   @param roundNb: the current round number. This shouldn't be a three digits number
*/
void updateRoundNbDisplay(int roundNb);

/* Update the trick number display
*   @param trickNb: the trick number from 1 to 8. 0 is a valid value meaning that the bidding phase is starting
*/
void updateTrickNbDisplay(int trickNb);

/* Update the team score display
*   @param players[]: array of 4 players
*/
void updateTeamScore(Player players[]);

/* Displays the trick that is being played. This display contains the color of the trump, the number of the trick, the game table and the user's hand
*   @param players: the array of the four players
*   @param trump: the color of the trump
*   @param contract: the contract of the round
*/
void displayTrick(Player* players, Color trump, Contract contract);

/* Changes the trick display by updating the hand of the user and the cards played on the table
*   @param playerPosition: the position of the player whp just played
*   @param playerCard: the card played by the player concerned
*   @param playerHand: the user's hand
*   @param nbOfCardsInHand: how many cards left in the user's hand
*/
void updateTrickDisplay(Position playerPosition, Card playedCard, Card* playerHand, int nbOfCardsInHand);

#endif // USERIO_H