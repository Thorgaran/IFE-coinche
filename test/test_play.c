#include "unity.h"
#include "core.h"
#include "play.h"
#include "cardUtils.h"
#include "userIO.h"
#include "ai.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_getCardPoints()
{
    Card cardArray[3] =
        {{.value = SEVEN, .color = HEART},
        { .value = JACK,  .color = HEART},
        { .value = ACE,   .color = HEART}};
    int cardPoints, expectedPoints[3][4] =
        {{0, 0, 0, 0},
        {2, 20, 2, 14},
        {11, 11, 19, 6}};
    char string[13];
    for (int i = 0; i <= 2; i++) {
        sprintf(string, "%d: not trump", i);
        cardPoints = getCardPoints(cardArray[i], NULL_COLOR);
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedPoints[i][0], cardPoints, string);
        sprintf(string, "%d: trump", i);
        cardPoints = getCardPoints(cardArray[i], HEART);
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedPoints[i][1], cardPoints, string);
        sprintf(string, "%d: NOTRUMP", i);
        cardPoints = getCardPoints(cardArray[i], NOTRUMP);
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedPoints[i][2], cardPoints, string);
        sprintf(string, "%d: ALLTRUMP", i);
        cardPoints = getCardPoints(cardArray[i], ALLTRUMP);
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedPoints[i][3], cardPoints, string);
    }
}

void test_getCardArrayPoints()
{
    Card cardDeck[32];
    int cardArrayPoints[6];
    createDeck(cardDeck);
    for (Color trump = SPADE; trump <= NOTRUMP; trump++) {
        cardArrayPoints[trump - 1] = getCardArrayPoints(cardDeck, 32, trump);
    }
    TEST_ASSERT_EACH_EQUAL_INT_MESSAGE(152, cardArrayPoints, 6, "Total sum must be 152");
}

void test_setCanPlay()
{
    Card cardArray[4] =
        {{.value = SEVEN, .color = SPADE, .canPlay = TRUE},
        { .value = JACK,  .color = HEART, .canPlay = TRUE},
        { .value = QUEEN, .color = HEART, .canPlay = TRUE},
        { .value = ACE,   .color = CLUB,  .canPlay = TRUE}};
    Bool conditionMet, cardArrayCanPlay[4], expectedCanPlay[4] = {FALSE, TRUE, FALSE, FALSE};
    conditionMet = setCanPlay(cardArray, 4, NULL_COLOR, HEART, 0, FALSE);
    TEST_ASSERT_TRUE_MESSAGE(conditionMet, "conditionMet set all to FALSE");
    for (int i = 0; i <= 3; i++) {
        TEST_ASSERT_FALSE_MESSAGE(cardArray[i].canPlay, "Set all to FALSE");
    }
    conditionMet = setCanPlay(cardArray, 4, DIAMOND, HEART, 0, TRUE);
    TEST_ASSERT_FALSE_MESSAGE(conditionMet, "conditionMet keep all to FALSE");
    for (int i = 0; i <= 3; i++) {
        TEST_ASSERT_FALSE_MESSAGE(cardArray[i].canPlay, "Keep all to FALSE");
    }
    conditionMet = setCanPlay(cardArray, 4, CLUB, CLUB, 27, TRUE);
    TEST_ASSERT_FALSE_MESSAGE(conditionMet, "conditionMet only weaker trump");
    for (int i = 0; i <= 3; i++) {
        TEST_ASSERT_FALSE_MESSAGE(cardArray[i].canPlay, "Only weaker trump");
    }
    conditionMet = setCanPlay(cardArray, 4, HEART, HEART, 25, TRUE);
    TEST_ASSERT_TRUE_MESSAGE(conditionMet, "conditionMet only stronger trump");
    for (int i = 0; i <= 3; i++) {
        cardArrayCanPlay[i] = cardArray[i].canPlay;
    }
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expectedCanPlay, cardArrayCanPlay, 4, "Only stronger trump");
}

void test_findValidCardsInHand() {
    Card cardsInHand[8] =
        {{.value = ACE,   .color = DIAMOND},
        { .value = JACK,  .color = SPADE  },
        { .value = KING,  .color = HEART  },
        { .value = SEVEN, .color = HEART  },
        { .value = TEN,   .color = HEART  },
        { .value = ACE,   .color = HEART  },
        { .value = NINE,  .color = CLUB   },
        { .value = SEVEN, .color = CLUB  }};
    Card trickCards[3] = 
        {{.value = EIGHT,  .color = CLUB  },
        { .value = JACK,  .color = DIAMOND},
        { .value = QUEEN, .color = HEART }};
    Bool expectedCanPlay[12][8] =
        {{TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
        { FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE},
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE},
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE},
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE},
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE},
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE },
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE },
        { FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE, FALSE},
        { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE},
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE}};
    findValidCardsInHand(cardsInHand, 8, trickCards, 0, SPADE);
    for (int i = 0; i <= 7; i++) {
        TEST_ASSERT_TRUE_MESSAGE(cardsInHand[i].canPlay, "First player");
    }
    for (int i = 0; i <= 7; i++) {
        findValidCardsInHand(cardsInHand, 8 - i, trickCards, 3, SPADE);
        for (int j = 7; j >= i; j--) {
            TEST_ASSERT_EQUAL_MESSAGE(expectedCanPlay[i][j], cardsInHand[7 - j].canPlay, "Reducing number of cards");
        }
    }
    trickCards[1].color = CLUB; //The partner is now winning
    findValidCardsInHand(cardsInHand, 6, trickCards, 3, SPADE);
    for (int i = 0; i <= 6; i++) {
        TEST_ASSERT_TRUE_MESSAGE(cardsInHand[i].canPlay, "Partner winning");
    }
    findValidCardsInHand(cardsInHand, 8, trickCards, 3, HEART);
    for (int i = 0; i <= 7; i++) {
        TEST_ASSERT_EQUAL_MESSAGE(expectedCanPlay[8][i], cardsInHand[i].canPlay, "Trump played but can play in trick color");
    }
    findValidCardsInHand(cardsInHand, 6, trickCards, 3, HEART);
    for (int i = 0; i <= 5; i++) {
        TEST_ASSERT_EQUAL_MESSAGE(expectedCanPlay[9][i], cardsInHand[i].canPlay, "Trump played and can play a better trump");
    }
    trickCards[2].value = JACK; //The trump card is now too strong to be played against
    findValidCardsInHand(cardsInHand, 6, trickCards, 3, HEART);
    for (int i = 0; i <= 5; i++) {
        TEST_ASSERT_EQUAL_MESSAGE(expectedCanPlay[10][i], cardsInHand[i].canPlay, "Trump played and can't play a better trump");
    }
    trickCards[1].color = DIAMOND; //Revert back to diamond
    findValidCardsInHand(cardsInHand, 8, trickCards, 3, ALLTRUMP);
    for (int i = 0; i <= 7; i++) {
        TEST_ASSERT_EQUAL_MESSAGE(expectedCanPlay[11][i], cardsInHand[i].canPlay, "ALLTRUMP and can play a better trump");
    }
}
void test_playTrick()
{
    Position trickWinner, expectedWinner[4][6] =
        {{SOUTH, WEST, NORTH, EAST, SOUTH, SOUTH},
         {SOUTH, WEST, NORTH, EAST, WEST,  WEST},
         {SOUTH, WEST, NORTH, EAST, NORTH, NORTH},
         {SOUTH, WEST, NORTH, EAST, EAST,  EAST}};
    int expectedScore[4][6][4] =
        {{{14, 0, 0, 0}, {0, 28, 0, 0}, {0, 0, 14, 0}, {0, 0, 0, 14}, {16, 0, 0, 0}, {22, 0, 0, 0}},
         {{14, 0, 0, 0}, {0, 28, 0, 0}, {0, 0, 14, 0}, {0, 0, 0, 14}, {0, 16, 0, 0}, {0, 22, 0, 0}},
         {{14, 0, 0, 0}, {0, 28, 0, 0}, {0, 0, 14, 0}, {0, 0, 0, 14}, {0, 0, 16, 0}, {0, 0, 22, 0}},
         {{14, 0, 0, 0}, {0, 28, 0, 0}, {0, 0, 14, 0}, {0, 0, 0, 14}, {0, 0, 0, 16}, {0, 0, 0, 22}}};
    for(Position startingPlayer = SOUTH; startingPlayer <= EAST; startingPlayer++) {
        for(Color trump = SPADE; trump <= NOTRUMP; trump++) {
            Card playerCards[4][1] =
                {{{.value = EIGHT, .color = SPADE  }},
                {{.value = NINE,  .color = HEART  }},
                {{.value = QUEEN, .color = DIAMOND}},
                {{.value = ACE,   .color = CLUB   }}};
            Player players[] = 
                {{.type = AI_FIRSTAVAILABLE, .pos = SOUTH, .score = 0, .nbOfCards = 1, .cards = playerCards[0]},
                { .type = AI_FIRSTAVAILABLE, .pos = WEST,  .score = 0, .nbOfCards = 1, .cards = playerCards[1]},
                { .type = AI_FIRSTAVAILABLE, .pos = NORTH, .score = 0, .nbOfCards = 1, .cards = playerCards[2]},
                { .type = AI_FIRSTAVAILABLE, .pos = EAST,  .score = 0, .nbOfCards = 1, .cards = playerCards[3]}};
            trickWinner = playTrick(players, startingPlayer, trump);
            TEST_ASSERT_EQUAL_MEMORY_MESSAGE(expectedWinner[startingPlayer][trump - 1], trickWinner, sizeof(Position), "Wrong winner");
            for(Position player = SOUTH; player <= EAST; player++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(0, players[player].nbOfCards, "NbOfCards not null");
                TEST_ASSERT_EQUAL_INT_MESSAGE(expectedScore[startingPlayer][trump - 1][player], players[player].score, "Wrong score");
            }
        }
    }
}

void test_playRound()
{
    int expectedScore[6][4] = {{26, 38, 71, 27}, {42, 79, 41, 0}, {41, 59, 30, 32}, {65, 71, 26, 0}, {46, 74, 27, 15}, {64, 58, 40, 0}};
    for(Position startingPlayer = SOUTH; startingPlayer <= EAST; startingPlayer++) {
        for(Color trump = SPADE; trump <= NOTRUMP; trump++) {
            Card playerCards[4][8] =
                {{{.value = ACE,  .color = HEART  }, {.value = ACE,   .color = SPADE  },
                { .value = QUEEN, .color = HEART  }, {.value = EIGHT, .color = SPADE  },
                { .value = QUEEN, .color = DIAMOND}, {.value = NINE,  .color = HEART  },
                { .value = JACK,  .color = CLUB   }, {.value = QUEEN, .color = CLUB   }},
                {{.value = JACK,  .color = HEART  }, {.value = KING,  .color = SPADE  },
                { .value = NINE,  .color = CLUB   }, {.value = TEN,   .color = SPADE  },
                { .value = SEVEN, .color = DIAMOND}, {.value = JACK,  .color = DIAMOND},
                { .value = SEVEN, .color = CLUB   }, {.value = ACE,   .color = CLUB   }},
                {{.value = TEN,   .color = HEART  }, {.value = QUEEN, .color = SPADE  },
                { .value = SEVEN, .color = HEART  }, {.value = JACK,  .color = SPADE  },
                { .value = TEN,   .color = DIAMOND}, {.value = ACE,   .color = DIAMOND},
                { .value = KING,  .color = HEART  }, {.value = TEN,   .color = CLUB   }},
                {{.value = EIGHT, .color = HEART  }, {.value = SEVEN, .color = SPADE  },
                { .value = KING,  .color = DIAMOND}, {.value = NINE,  .color = SPADE  },
                { .value = EIGHT, .color = DIAMOND}, {.value = NINE,  .color = DIAMOND},
                { .value = EIGHT, .color = CLUB   }, {.value = KING,  .color = CLUB   }}};
            Player players[] = 
                {{.type = AI_FIRSTAVAILABLE, .pos = SOUTH, .score = 0, .nbOfCards = 8, .cards = playerCards[0]},
                { .type = AI_FIRSTAVAILABLE, .pos = WEST,  .score = 0, .nbOfCards = 8, .cards = playerCards[1]},
                { .type = AI_FIRSTAVAILABLE, .pos = NORTH, .score = 0, .nbOfCards = 8, .cards = playerCards[2]},
                { .type = AI_FIRSTAVAILABLE, .pos = EAST,  .score = 0, .nbOfCards = 8, .cards = playerCards[3]}};
            play(players, startingPlayer, trump);
            for(Position player = SOUTH; player <= EAST; player++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(0, players[player].nbOfCards, "NbOfCards not null");
                TEST_ASSERT_EQUAL_INT_MESSAGE(expectedScore[trump - 1][player], players[player].score, "Wrong score");
            }
        }
    }
}