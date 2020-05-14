#include "unity.h"
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

void test_getPlayerCard()
{
    TEST_IGNORE_MESSAGE("To do after each individual getCard test");
}

void test_getTeamRoundPoints()
{
    Player players[4] = {{.score = 0}, {.score = 0}, {.score = 0}, {.score = 0}};
    int roundScore, expectedScore[4] = {114, 48, 114, 48};
    for (Position player = SOUTH; player <= EAST; player++) {
        roundScore = getTeamRoundPoints(players, player);
        TEST_ASSERT_EQUAL_INT_MESSAGE(0, roundScore, "Score is not null");
    }
    players[0].score = 47;
    players[1].score = 48;
    players[2].score = 67;
    for (Position player = SOUTH; player <= EAST; player++) {
        roundScore = getTeamRoundPoints(players, player);
        TEST_ASSERT_EQUAL_INT_MESSAGE(expectedScore[player], roundScore, "Score missmatch");
    }
}

void test_increaseTeamTotalScore() {
    Player players[4] = {{.teamScore = 682}, {.teamScore = 123}, {.teamScore = 682}, {.teamScore = 123}};
    int totalScore, startScore[4] = {682, 123, 682, 123}, expectedTeamScore[4][4] =
        {{724, 123, 724, 123}, {682, 165, 682, 165}, {724, 123, 724, 123}, {682, 165, 682, 165}};
    for (Position player = SOUTH; player <= EAST; player++) {
        increaseTeamTotalScore(players, player, 42);
        for (Position testPlayer = SOUTH; testPlayer <= EAST; testPlayer++) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(expectedTeamScore[player][testPlayer], players[testPlayer].teamScore, "Wrong team score");
            players[testPlayer].teamScore = startScore[testPlayer];
        }
    }
}