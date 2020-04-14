#include <stdio.h>
#include <stdlib.h>
#include "coinche.h"

/* Function that defines the "strength" of a played card in order to know which player wins the trick
*   @param card: the evaluated card
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return cardStrength -> an integer that defines the "strength" of the card, the card with the greatest "strength" wins the trick
*/
int getCardStrength(cardType card, colorType trump, colorType roundColor){
    int cardStrength = card.value;

    if(card.color == roundColor)
        cardStrength += 10;                             // If the card has the right color, its strength increases

    if((trump == card.color) || (trump == ALLTRUMP)){
        cardStrength += 18;                             // If the card is a trump, its strength increases
        if((card.value == NINE) || (card.value == JACK))
            cardStrength += 6;                          // If the card is a trump and a 9 or a jack, its strength increases again according to the belotte rules
    }
    return cardStrength;
}

/* Function that finds the player who wins the trick based on the played cards
*   @param *cardArray: the array that contains the cards of the round
*   @param numberOfCards: how many cards were played during the round (4 for the coinche)
*   @param trump: the current trump
*   @param roundColor: the color of the first played card in the round
*   @return playerNumber -> the number of the player who wins the trick, with 0 being the first player
*/
int getTrickWinner(cardType *cardArray, int numberOfCards, colorType trump, colorType roundColor) {
    int greatestStrength = getCardStrength(cardArray[0], trump, roundColor);
    int cardStrength;
    int trickWinner = 0;

    for (int i = 1; i < numberOfCards; i++) {
        cardStrength = getCardStrength(cardArray[i], trump, roundColor); //cardStrength is needed to avoid calling getCardStrength twice
        if (cardStrength > greatestStrength) {
           greatestStrength = cardStrength;
           trickWinner = i;
        }
    }
    return trickWinner;
}