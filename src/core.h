#ifndef CORE_H
#define CORE_H

#define MAX_PLAYER_NAME_LENGTH 50

/**
 * \enum Bool
*/
typedef enum Bool {
    FALSE = 0,
    TRUE = 1
} Bool;

/**
 * \enum Value
*/
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

/**
 * \enum Color
*/
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

/**
 * \enum CardAI
*/
typedef enum CardAI {
    CARD_USER              = 0,
    CARD_AI_FIRSTAVAILABLE = 1,
    CARD_AI_STANDARD       = 2
} CardAI;
#define NB_CARD_AI 3

/**
 * \enum ContractAI
*/
typedef enum ContractAI {
    CONTRACT_USER            = 0,
    CONTRACT_AI_ALWAYSEIGHTY = 1,
    CONTRACT_AI_STANDARD     = 2
} ContractAI;
#define NB_CONTRACT_AI 3

/**
 * \enum Position
*/
typedef enum Position {
    SOUTH = 0,
    WEST  = 1,
    NORTH = 2,
    EAST  = 3
} Position;

typedef struct Player {
    CardAI cardAI;
    ContractAI contractAI;
    Position pos;
    char* name;
    char* croppedName;
    Card* cards;
    int nbOfCards;
    int score;
    int teamScore;
} Player;

/**
 * \enum Coinche
*/
typedef enum Coinche {
    NOT_COINCHED = 0,
    COINCHED     = 1,
    OVERCOINCHED = 2
} Coinche;

/**
 * \enum ContractType
*/
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

/**
 * \enum TextPosition
*/
typedef enum TextPosition {
    TEXT_LEFT = 0,
    TEXT_CENTER = 1,
    TEXT_RIGHT = 2
} TextPosition;

/**
 * \def const int CARD_POINTS_TABLE[4][8]
*/
const int CARD_POINTS_TABLE[4][8];

/**
 * \def const char* VALUE_STR_TABLE[9][2]
*/
const char* VALUE_STR_TABLE[9][2];

/**
 * \def const char* COLOR_STR_TABLE[7][2]
*/
const char* COLOR_STR_TABLE[7][2];

/**
 * \def const char* COINCHE_STR_TABLE[3]
*/
const char* COINCHE_STR_TABLE[3];

/**
 * \def const char* CONTRACTTYPE_STR_TABLE[3]
*/
const char* CONTRACTTYPE_STR_TABLE[3];

/**
 * \def const char* CARDAI_STR_TABLE[NB_CARD_AI]
*/
const char* CARDAI_STR_TABLE[NB_CARD_AI];

/**
 * \def const char* CONTRACTAI_STR_TABLE[NB_CONTRACT_AI]
*/
const char* CONTRACTAI_STR_TABLE[NB_CONTRACT_AI];

#endif // CORE_H