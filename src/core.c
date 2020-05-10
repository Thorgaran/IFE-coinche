const int CARD_POINTS_TABLE[4][8] = {  //Array used to determine the point value of a card. Read only.
//  {SEVEN, EIGHT,  NINE,  JACK, QUEEN,  KING,   TEN,   ACE}
    {    0,     0,     9,    14,     1,     3,     5,     6},  //If ALLTRUMP
    {    0,     0,     0,     2,     3,     4,    10,    19},  //If NOTRUMP
    {    0,     0,    14,    20,     3,     4,    10,    11},  //If the card is a trump
    {    0,     0,     0,     2,     3,     4,    10,    11},  //If the card is not a trump
};