#ifndef USERIO_H
#define USERIO_H
#include "core.h"

/* Ask the user for an int between two positive numbers
*   @param minBound: the minimum valid value the user can enter (must be a positive int)
*   @param maxBound: the maximum valid value the user can enter (must be a positive int)
*   @return userVal: the value entered by the user, guaranteed to be an int between minBound and maxBound
*/
int inputUserInt(int minBound, int maxBound, char* displayStr);

Card askUserCard(Card cardArray[], int nbOfCards);

Bool askUserContract(Card cardArray[], int nbOfCards, Contract *contract);

#endif // USERIO_H