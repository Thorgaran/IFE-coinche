#ifndef _BID_H_
#define _BID_H_
#include "core.h"

/* Play a bid attempt: either a contract is made or everyone passed
*   @param players[]: array of 4 players
*   @param startingPlayer: position of the starting player
*   @param *contract: pointer to the contract being debated. Will be edited someone decides to make a contract
*   @return everyonePassed: FALSE if a contract was made, TRUE otherwise
*/
Bool bidAttempt(Player players[], Position startingPlayer, Contract *contract);

/* Deal cards and play bid attempts until a contract is made
*   @param players[]: array of 4 players
*   @param startingPlayer: position of the starting player
*   @return contract: the contract that was made
*/
Contract bid(Player players[], Position startingPlayer);

#endif