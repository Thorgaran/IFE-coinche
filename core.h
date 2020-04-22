#ifndef _CORE_H_
#define _CORE_H_

typedef enum Bool {
    FALSE = 0,
    TRUE = 1
} Bool;

typedef enum Value {
    NULL_VALUE = 0,
    SEVEN      = 1,
    EIGHT      = 2,
    NINE       = 3,
    JACK       = 4,
    QUEEN      = 5,
    KING       = 6,
    TEN        = 7,
    ACE        = 8
} Value;

typedef enum Color {
    NULL_COLOR = 0,
    SPADE      = 1,
    HEART      = 2,
    DIAMOND    = 3,
    CLUB       = 4,
    ALLTRUMP   = 5,
    NOTRUMP    = 6
} Color;

typedef struct Card {
    Value value;
    Color color;
    Bool canPlay;
} Card;

typedef struct Player {
    char *name;
    Card *cards;
    int nbOfCards;
    int score;
    Bool isUser;
} Player;

const int CARD_POINTS_TABLE[4][8];

#endif