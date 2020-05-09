#ifndef _BID_H_
#define _BID_H_
#include "core.h"

/* Get the player to decide whether or not to make a contract, depending on the player type (User/AI)
*   @param player: the player who has to make a decision
*   @param *contract: pointer to the contract being debated. Will be edited if the player decides to make a contract
*   @return hasPassed: TRUE if the player has decided to pass, FALSE if the player decided to make a contract
*/
Bool getPlayerContract(Player player, Contract *contract);

#endif