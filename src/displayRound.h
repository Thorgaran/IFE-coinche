#ifndef USERIO_H
#define USERIO_H
#include "core.h"

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
*   @param card: the card to display. Only its value and color matter. Depending on its color, the card will be displayed in red or white
*/
void changeCardDisplay(Card card);

/* Displays an empty play table
*/
void displayTable(void);

/* Clears top-right box. The cursor is left untouched
*/
void clearTopRightBox(void);

/* Displays an empty "Last trick" template in the top-right box. The cursor is left untouched
*/
void prepareLastTrickDisplay(void);

/* Displays a single line in the top-right box. The cursor is moved to the next line
*   @param lineToDisplay[]: the string to display, must contain a maximum of 15 characters
*   @param firstline: set to TRUE if this is the first line of the menu to display, set to FALSE otherwise
*   @param lastLine: set to TRUE if this is the last line of the menu to display, set to FALSE otherwise
*/
void displayBiddingMenuLine(char lineToDisplay[], Bool firstLine, Bool lastLine);

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

#endif // USERIO_H