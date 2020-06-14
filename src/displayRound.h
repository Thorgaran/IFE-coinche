#ifndef USERIO_H
#define USERIO_H
#include "core.h"

/**
 * \fn void displayEmptyCard(void)
 * 
 * Displays an empty card at the current cursor position (the cursor comes back to that position afterwards)
*/
void displayEmptyCard(void);

/**
 * \fn void deleteCardDisplay(void)
 * 
 * Deletes a card at the current cursor position (the cursor comes back to that position afterwards)
*/
void deleteCardDisplay(void);

/** 
 * \fn void clearCardDisplay(void)
 * 
 * Clears a card at the current cursor position (the cursor comes back to that position afterwards)
*/
void clearCardDisplay(void);

/** 
 * \fn void changeCardDisplay(Card card)
 * @param card: the card to display. Only its value and color matter. Depending on its color, the card will be displayed in red or white
 * 
 * Changes a card at the current cursor position (the cursor comes back to that position afterwards)
*/
void changeCardDisplay(Card card);

/** 
 * \fn void preparePlayTable(void)
 * 
 * Prepares the play phase by displaying everything needed
*/
void preparePlayTable(void);

/** 
 * \fn void clearTopRightBox(void)
 * 
 * Clears top-right box. The cursor is left untouched
*/
void clearTopRightBox(void);

/** 
 * \fn void prepareLastTrickDisplay(void)
 * 
 * Displays an empty "Last trick" template in the top-right box. The cursor is left untouched
*/
void prepareLastTrickDisplay(void);

/** 
 * \fn void displayBiddingMenuLine(char lineToDisplay[], Bool firstLine, Bool lastLine)
 * @param lineToDisplay[]: the string to display, must contain a maximum of 15 characters
 * @param firstline: set to TRUE if this is the first line of the menu to display, set to FALSE otherwise
 * @param lastLine: set to TRUE if this is the last line of the menu to display, set to FALSE otherwise
 * 
 * Displays a single line in the top-right box. The cursor is moved to the next line
*/
void displayBiddingMenuLine(char lineToDisplay[], Bool firstLine, Bool lastLine);

/** 
 * \fn void clearContractDisplay(void)
 * 
 *  Clears contract display. The cursor is left untouched
*/
void clearContractDisplay(void);

/** 
 * \fn void updateContractDisplay(char playerName[], Contract contract)
 * @param playerName: the contract issuer's name
 * @param contract: the contract to display
 * 
 * Fills in the contract table corner with a given contract
*/
void updateContractDisplay(char playerName[], Contract contract);

/** 
 * \fn 
 * Displays a centered, cropped player name at the right place on the table, optionnally underlined
*   @param player: the player whose name should be displayed
*   @param underline: TRUE if the name sould be underlined, FALSE otherwise
*/
void displayPlayerName(Player player, Bool underline);

/** 
 * \fn 
 * Replaces the old displayed round value with a new one
*   @param roundNb: the current round number. This shouldn't be a three digits number
*/
void updateRoundNbDisplay(int roundNb);

/** 
 * \fn 
 * Updates the trick number display
*   @param trickNb: the trick number from 1 to 8. 0 is a valid value meaning that the bidding phase is starting
*/
void updateTrickNbDisplay(int trickNb);

/** 
 * \fn 
 * Updates the team score display
*   @param players[]: array of 4 players
*/
void updateTeamScore(Player players[]);

/** 
 * \fn 
 * Updates the last trick display with new cards
*   @param lastTrickCards[]: 4-card array containing the previous trick cards
*   @param startingPlayer: position of the starting player of the previous trick
*/
void updateLastTrickDisplay(Card lastTrickCards[], Position startingPlayer);

/** 
 * \fn void clearLastTrickDisplay(void)
 * 
 * Clears the 4 cards in the last trick display
*/
void clearLastTrickDisplay(void);

/** 
 * \fn void displayTrickCard(Card playedCard, Position currentPlayer)
 * @param playedCard: the card to display
 * @param currentPlayer: position of the player who just played the last card
 * 
 * Displays a trick card in the middle of the table
*/
void displayTrickCard(Card playedCard, Position currentPlayer);

/** 
 * \fn void deleteDisplayedTrickCards(void)
 * 
 * Deletes all 4 currently displayed trick cards
*/
void deleteDisplayedTrickCards(void);

/** 
 * \fn void displayNumbersAbovePlayerHand(Card cardsInHand[], int nbOfCardsInHand)
 * @param cardInHand[]: array containing the player's cards (only the canPlay property is looked at)
 * @param nbOfCardsInHand: the number of cards in the SOUTH player's hand
 * 
 * Displays a line of sequencial numbers above the player's hand cards that can be played
*/
void displayNumbersAbovePlayerHand(Card cardsInHand[], int nbOfCardsInHand);

/** 
 * \fn void displayPlayerHand(Card cardsInHand[], int nbOfCardsInHand)
 * @param cardsInHand[]: array containing the player's cards
 * @param nbOfCardsInHand: the number of cards in cardsInHand
 * 
 * Displays the player's hand, centered
*/
void displayPlayerHand(Card cardsInHand[], int nbOfCardsInHand);

/** 
 * \fn void deletePlayerHand(void)
 * 
 * Deletes the content of the five lines (including the numbers line) containing the displayed player hand
*/
void deletePlayerHand(void);

/** 
 * \fn void updatePlayerTrickPoints(int points, Position playerPos)
 * @param points: the player's trick points
 * @param playerPos: the position the player
 * 
 * Displays the current trick points of a player near its name 
*/
void updatePlayerTrickPoints(int points, Position playerPos);

/** 
 * \fn void clearDisplayedTrickPoints(void)
 * 
 * Clears all 4 displayed trick points
*/
void clearDisplayedTrickPoints(void);

#endif // USERIO_H