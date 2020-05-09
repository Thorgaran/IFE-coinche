#ifndef _USERIO_H_
#define _USERIO_H_
#include "core.h"

Card askUserCard(Card *cardArray, int nbOfCards);

Bool askUserContract(Card *cardArray, int nbOfCards, Contract *contract);

#endif