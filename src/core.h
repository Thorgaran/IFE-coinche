#ifndef CORE_H
#define CORE_H

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

typedef enum cardAI {
    CARD_USER              = 0,
    CARD_AI_FIRSTAVAILABLE = 1,
    CARD_AI_STANDARD       = 2
} cardAI;

typedef enum contractAI {
    CONTRACT_USER            = 0,
    CONTRACT_AI_ALWAYSEIGHTY = 1,
    CONTRACT_AI_STANDARD     = 2
} contractAI;

typedef enum Position {
    SOUTH = 0,
    WEST  = 1,
    NORTH = 2,
    EAST  = 3
} Position;

typedef struct Player {
    cardAI cardAI;
    contractAI contractAI;
    Position pos;
    char *name;
    Card *cards;
    int nbOfCards;
    int score;
    int teamScore;
} Player;

typedef enum Coinche {
    NOT_COINCHED = 0,
    COINCHED     = 1,
    OVERCOINCHED = 2
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

#endif // CORE_H