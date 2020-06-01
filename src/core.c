const int CARD_POINTS_TABLE[4][8] = { //Array used to determine the point value of a card. Read only
//  {SEVEN, EIGHT,  NINE,  JACK, QUEEN,  KING,   TEN,   ACE}
    {    0,     0,     9,    14,     1,     3,     5,     6},  //If ALLTRUMP
    {    0,     0,     0,     2,     3,     4,    10,    19},  //If NOTRUMP
    {    0,     0,    14,    20,     3,     4,    10,    11},  //If the card is a trump
    {    0,     0,     0,     2,     3,     4,    10,    11},  //If the card is not a trump
};

const char* VALUE_STR_TABLE[9] = { //Array used to convert between valur types and their string representations. Read only
    " ",    //NULL_VALUE
    "7 ",   //SEVEN
    "8 ",   //EIGHT
    "9 ",   //NINE
    "J ",   //JACK
    "Q ",   //QUEEN
    "K ",   //KING
    "10",   //TEN
    "A "    //ACE
};

const char* COLOR_STR_TABLE[7] = { //Array used to convert between color types and their string representations. Read only
    " ",        //NULL_COLOR
    "♠",        //SPADE
    "♥",        //HEART
    "♦",        //DIAMOND
    "♣",        //CLUB
    "All trump",//ALLTRUMP
    "No trump"  //NOTRUMP
};

const char* COINCHE_STR_TABLE[3] = { //Array used to convert between coinche types and their string representations. Read only
    "",             //NOT_COINCHED
    "Coinched",     //COINCHED
    "Overcoinched"  //OVERCOINCHED
};

const char* CONTRACTTYPE_STR_TABLE[3] = { //Array used to convert between contractType types and their string representations. Read only
    "",         //POINTS
    "Capot",    //CAPOT
    "General"   //GENERAL
};