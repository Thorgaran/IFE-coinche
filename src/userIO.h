#ifndef USERIO_H
#define USERIO_H
#include "core.h"

Card askUserCard(Card cardArray[], int nbOfCards);

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract);

/* Displays a card at the current cursor position (the cursor comes back to that position afterwards)
*   @param card: the card to display. Only its value and color matter
*/
void displayCard(Card card);

/* Changes a card at the current cursor position (the cursor comes back to that position afterwards)
*   @param card: the card to display. Only its value and color matter
*/
void changeCardDisplay(Card card);

/* Displays the table with no informations
*/
void blankTable(void);

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