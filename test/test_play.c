#include "unity.h"
#include "core.h"
#include "play.h"
#include "cardUtils.h"
#include "playerUtils.h"
#include "userIO.h"
#include "ai.h"

void setUp(void)
{
}

void tearDown(void)
{
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
            playRound(players, startingPlayer, trump);
            for(Position player = SOUTH; player <= EAST; player++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(0, players[player].nbOfCards, "NbOfCards not null");
                TEST_ASSERT_EQUAL_INT_MESSAGE(expectedScore[trump - 1][player], players[player].score, "Wrong score");
            }
        }
    }
}