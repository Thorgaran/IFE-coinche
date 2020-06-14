/**
 * \file core.c
*/
#include "core.h"

const int CARD_POINTS_TABLE[4][8] = { //Array used to determine the point value of a card. Read only
//  {SEVEN, EIGHT,  NINE,  JACK, QUEEN,  KING,   TEN,   ACE}
    {    0,     0,     9,    14,     1,     3,     5,     6},  //If ALLTRUMP
    {    0,     0,     0,     2,     3,     4,    10,    19},  //If NOTRUMP
    {    0,     0,    14,    20,     3,     4,    10,    11},  //If the card is a trump
    {    0,     0,     0,     2,     3,     4,    10,    11},  //If the card is not a trump
};

const char* VALUE_STR_TABLE[9][2] = { //Array used to convert between Value types and their string representations. Read only
    {"", ""},       //NULL_VALUE
    {"7 ", "7"},    //SEVEN
    {"8 ", "8"},    //EIGHT
    {"9 ", "9"},    //NINE
    {"J ", "J"},    //JACK
    {"Q ", "Q"},    //QUEEN
    {"K ", "K"},    //KING
    {"10", "10"},   //TEN
    {"A ", "A"}     //ACE
};

const char* COLOR_STR_TABLE[7][2] = { //Array used to convert between Color types and their string representations. Read only
    {"", ""},                           //NULL_COLOR
    {"♠", " spade"},                    //SPADE
    {"\033[0;31m♥\033[0m", " heart"},   //HEART (in red)
    {"\033[0;31m♦\033[0m", " diamond"}, //DIAMOND (in red)
    {"♣", " club"},                     //CLUB
    {"All trump", "n all trump"},       //ALLTRUMP
    {"No trump", "no trump"}            //NOTRUMP
};

const char* COINCHE_STR_TABLE[3] = { //Array used to convert between Coinche types and their string representations. Read only
    "",             //NOT_COINCHED
    "Coinched",     //COINCHED
    "Overcoinched"  //OVERCOINCHED
};

const char* CONTRACTTYPE_STR_TABLE[3] = { //Array used to convert between ContractType types and their string representations. Read only
    "",         //POINTS
    "Capot",    //CAPOT
    "General"   //GENERAL
};

const char* CARDAI_STR_TABLE[NB_CARD_AI] = { //Array used to convert between CardAI types and their string representations. Read only
    "User",
    "First available",
    "Standard"
};

const char* CONTRACTAI_STR_TABLE[NB_CONTRACT_AI] = { //Array used to convert between ContractAI types and their string representations. Read only
    "User",
    "Always eighty",
    "Standard",
    "Advanced"
};