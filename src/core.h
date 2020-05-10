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

typedef enum PlayerType {
    USER              = 0,
    AI_FIRSTAVAILABLE = 1,
    AI_STANDARD       = 2
} PlayerType;

typedef enum Position {
    SOUTH = 0,
    WEST  = 1,
    NORTH = 2,
    EAST  = 3
} Position;

typedef struct Player {
    PlayerType type;
    Position pos;
    char *name;
    Card *cards;
    int nbOfCards;
    int score;
} Player;

typedef enum Coinche {
    NORMAL      = 0,
    COINCHE     = 1,
    OVERCOINCHE = 2
} Coinche;

typedef enum ContractType {
    POINTS  = 0,
    CAPOT   = 1,
    GENERAL = 2
} ContractType;

typedef struct Contract {
    Color trump;
    ContractType type;
    int points;
    Coinche coinche;
    Position issuer;
} Contract;

const int CARD_POINTS_TABLE[4][8];

#endif