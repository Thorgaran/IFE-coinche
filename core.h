#ifndef _CORE_H_
#define _CORE_H_

typedef enum bool {
    FALSE = 0,
    TRUE = 1
} bool;

typedef enum valueType {
    NULL_VALUE = 0,
    SEVEN      = 1,
    EIGHT      = 2,
    NINE       = 3,
    JACK       = 4,
    QUEEN      = 5,
    KING       = 6,
    TEN        = 7,
    ACE        = 8,
    TRUMP_NINE = 9,
    TRUMP_JACK = 10
} valueType;

typedef enum colorType {
    NULL_COLOR = 0,
    SPADE      = 1,
    HEART      = 2,
    DIAMOND    = 3,
    CLOVER     = 4,
    ALLTRUMP   = 5,
    NOTRUMP    = 6
} colorType;

typedef struct cardType {
    valueType value;
    colorType color;
    bool canPlay;
} cardType;

const int CARD_POINTS_TABLE[4][8];

#endif