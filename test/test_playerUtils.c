#include "unity.h"
#include "cardUtils.h"
#include "playerUtils.h"
#include "stringUtils.h"
#include "userInput.h"
#include "ai.h"
#include "displayMain.h"
#include "displayRound.h"
#include "leaderboard.h"

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

void test_cardsDistribution()
{
    Bool foundCard;
    Card cardDeck[32], playerCards[4][8];
    Player players[4] =
        {{.nbOfCards = 8, .cards = playerCards[0]},
         {.nbOfCards = 8, .cards = playerCards[1]},
         {.nbOfCards = 8, .cards = playerCards[2]},
         {.nbOfCards = 8, .cards = playerCards[3]}};
    int nbOfCardsLeft = 32;
    createDeck(cardDeck);
    cardsDistribution(players);
    for (Position player = SOUTH; player <= EAST; player++) {
        for (int cardIndex = 0; cardIndex < 8; cardIndex++) {
            foundCard = removeCard(cardDeck, &nbOfCardsLeft, players[player].cards[cardIndex]);
            TEST_ASSERT_TRUE_MESSAGE(foundCard, "The card has not been found");
        }
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, nbOfCardsLeft, "There are some cards left");
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