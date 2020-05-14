#include "unity.h"
#include "core.h"
#include "cardUtils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_getCardStrength()
{
    Card card = {.color = SPADE, .value = SEVEN};
    int strength;
    strength = getCardStrength(card, NOTRUMP, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, strength, "SEVEN, NOTRUMP");
    strength = getCardStrength(card, CLUB, DIAMOND);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, strength, "SEVEN, other colors");
    strength = getCardStrength(card, NULL_COLOR, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(11, strength, "SEVEN, right color");
    strength = getCardStrength(card, SPADE, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(19, strength, "SEVEN, trump");
    strength = getCardStrength(card, ALLTRUMP, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(19, strength, "SEVEN, ALLTRUMP");
    strength = getCardStrength(card, SPADE, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(29, strength, "SEVEN, right color and trump");
    card.value = JACK;
    card.color = CLUB;
    strength = getCardStrength(card, NULL_COLOR, CLUB);
    TEST_ASSERT_EQUAL_INT_MESSAGE(14, strength, "JACK, right color");
    strength = getCardStrength(card, CLUB, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(28, strength, "JACK, trump");
    strength = getCardStrength(card, CLUB, CLUB);
    TEST_ASSERT_EQUAL_INT_MESSAGE(38, strength, "JACK, right color and trump");
}

void test_getStrongestCard()
{
    Card cardArraySingle[1] = {{.value = ACE, .color = HEART}};
    Card cardArrayTriple[4] =
        {{.value = SEVEN, .color = SPADE},
        { .value = JACK,  .color = HEART},
        { .value = QUEEN, .color = HEART},
        { .value = ACE,   .color = CLUB}};
    int strongestCard;
    strongestCard = getStrongestCard(cardArraySingle, 1, NULL_COLOR, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, strongestCard, "Single card");
    strongestCard = getStrongestCard(cardArrayTriple, 4, NULL_COLOR, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(3, strongestCard, "No strong colors");
    strongestCard = getStrongestCard(cardArrayTriple, 4, NULL_COLOR, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, strongestCard, "Round color");
    strongestCard = getStrongestCard(cardArrayTriple, 4, NULL_COLOR, HEART);
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, strongestCard, "Round color difference between JACK and QUEEN");
    strongestCard = getStrongestCard(cardArrayTriple, 4, HEART, CLUB);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, strongestCard, "Round and trump color difference between JACK and QUEEN");
    strongestCard = getStrongestCard(cardArrayTriple, 4, ALLTRUMP, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, strongestCard, "ALLTRUMP round color");
}

void test_sortCards()
{
    Card cardArray[4] =
        {{.value = EIGHT, .color = SPADE,   .canPlay = TRUE},
        { .value = NINE,  .color = DIAMOND, .canPlay = TRUE},
        { .value = QUEEN, .color = DIAMOND, .canPlay = TRUE},
        { .value = KING,  .color = CLUB,    .canPlay = TRUE}};
    Card cardArraySorted[4] =
        {{.value = EIGHT, .color = SPADE,   .canPlay = TRUE},
        { .value = NINE,  .color = DIAMOND, .canPlay = TRUE},
        { .value = QUEEN, .color = DIAMOND, .canPlay = TRUE},
        { .value = KING,  .color = CLUB,    .canPlay = TRUE}};
    Card cardArrayReverse[4] =
        {{.value = QUEEN, .color = DIAMOND, .canPlay = TRUE},
        { .value = KING,  .color = CLUB,    .canPlay = TRUE},
        { .value = NINE,  .color = DIAMOND, .canPlay = TRUE},
        { .value = EIGHT, .color = SPADE,   .canPlay = TRUE}};
    sortCards(cardArray, 4, NOTRUMP, NULL_COLOR);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardArraySorted, cardArray, sizeof(Card), 4, "Already sorted");
    sortCards(cardArray, 4, ALLTRUMP, SPADE);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardArrayReverse, cardArray, sizeof(Card), 4, "Reverse order (2-3-1-0)");
}

void test_removeCard()
{
    Card cardArrayToRemove[4] =
        {{.value = EIGHT, .color = SPADE},
        { .value = NINE,  .color = HEART},
        { .value = JACK,  .color = CLUB },
        { .value = ACE,   .color = SPADE}};
    Card cardArrayFirst[2] =
        {{.value = NINE,  .color = HEART},
        { .value = JACK,  .color = CLUB}};
    Card cardArrayMiddle[2] =
        {{.value = EIGHT, .color = SPADE},
        { .value = JACK,  .color = CLUB}};
    Card cardArrayLast[2] =
        {{.value = EIGHT, .color = SPADE},
        { .value = NINE,  .color = HEART}};
    Card *cardPointerArray[4] = {cardArrayFirst, cardArrayMiddle, cardArrayLast, cardArrayToRemove};
    int nbOfCards, nbOfElementsToCompare[4] = {2, 2, 2, 3};
    Bool foundCard, expectedFoundCard[4] = {TRUE, TRUE, TRUE, FALSE};
    char string[23];
    for (int i = 0; i <= 3; i++) {
        Card cardArray[3] =
            {{.value = EIGHT, .color = SPADE},
            { .value = NINE,  .color = HEART},
            { .value = JACK,  .color = CLUB}};
        nbOfCards = 3;
        foundCard = removeCard(cardArray, &nbOfCards, cardArrayToRemove[i]);
        sprintf(string, "%d: foundCard", i);
        TEST_ASSERT_TRUE_MESSAGE(foundCard == expectedFoundCard[i], string);
        sprintf(string, "%d: nbOfCards", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(nbOfCards, nbOfElementsToCompare[i], string);
        sprintf(string, "%d: Array after removal", i);
        TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardPointerArray[i], cardArray, sizeof(Card), nbOfElementsToCompare[i], string);
    }
}

void test_getPlayableCards()
{
    Card cardArray[2] =
        {{.value = EIGHT, .color = SPADE, .canPlay = TRUE},
        { .value = ACE,   .color = SPADE, .canPlay = TRUE}};
    Card cardArrayExpected[2] =
        {{.value = EIGHT, .color = SPADE, .canPlay = TRUE},
        { .value = ACE,   .color = SPADE, .canPlay = TRUE}};
    int nbOfPlayableCards;
    { Card playableCards[2];
    nbOfPlayableCards = getPlayableCards(cardArray, 2, playableCards);
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, nbOfPlayableCards, "nbOfPlayableCards, canPlay both");
    TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardArrayExpected, playableCards, sizeof(Card), 2, "array, canPlay both");
    }
    { cardArray[1].canPlay = FALSE;
    Card playableCards[1];
    nbOfPlayableCards = getPlayableCards(cardArray, 2, playableCards);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, nbOfPlayableCards, "nbOfPlayableCards, canPlay first");
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&(cardArrayExpected[0]), &(playableCards[0]), sizeof(Card), "array, canPlay first");
    }
    { cardArray[0].canPlay = FALSE;
    cardArray[1].canPlay = TRUE;
    Card playableCards[1];
    nbOfPlayableCards = getPlayableCards(cardArray, 2, playableCards);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, nbOfPlayableCards, "nbOfPlayableCards, canPlay second");
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&(cardArrayExpected[1]), &(playableCards[0]), sizeof(Card), "array, canPlay second");
    }
}

void test_createDeck()
{
    Card cardDeck[32], expectedCardDeck[32] = 
        {{.value = SEVEN, .color = SPADE  , .canPlay = FALSE},
        { .value = EIGHT, .color = SPADE  , .canPlay = FALSE},
        { .value = NINE,  .color = SPADE  , .canPlay = FALSE},
        { .value = JACK,  .color = SPADE  , .canPlay = FALSE},
        { .value = QUEEN, .color = SPADE  , .canPlay = FALSE},
        { .value = KING,  .color = SPADE  , .canPlay = FALSE},
        { .value = TEN,   .color = SPADE  , .canPlay = FALSE},
        { .value = ACE,   .color = SPADE  , .canPlay = FALSE},
        { .value = SEVEN, .color = HEART  , .canPlay = FALSE},
        { .value = EIGHT, .color = HEART  , .canPlay = FALSE},
        { .value = NINE,  .color = HEART  , .canPlay = FALSE},
        { .value = JACK,  .color = HEART  , .canPlay = FALSE},
        { .value = QUEEN, .color = HEART  , .canPlay = FALSE},
        { .value = KING,  .color = HEART  , .canPlay = FALSE},
        { .value = TEN,   .color = HEART  , .canPlay = FALSE},
        { .value = ACE,   .color = HEART  , .canPlay = FALSE},
        { .value = SEVEN, .color = DIAMOND, .canPlay = FALSE},
        { .value = EIGHT, .color = DIAMOND, .canPlay = FALSE},
        { .value = NINE,  .color = DIAMOND, .canPlay = FALSE},
        { .value = JACK,  .color = DIAMOND, .canPlay = FALSE},
        { .value = QUEEN, .color = DIAMOND, .canPlay = FALSE},
        { .value = KING,  .color = DIAMOND, .canPlay = FALSE},
        { .value = TEN,   .color = DIAMOND, .canPlay = FALSE},
        { .value = ACE,   .color = DIAMOND, .canPlay = FALSE},
        { .value = SEVEN, .color = CLUB   , .canPlay = FALSE},
        { .value = EIGHT, .color = CLUB   , .canPlay = FALSE},
        { .value = NINE,  .color = CLUB   , .canPlay = FALSE},
        { .value = JACK,  .color = CLUB   , .canPlay = FALSE},
        { .value = QUEEN, .color = CLUB   , .canPlay = FALSE},
        { .value = KING,  .color = CLUB   , .canPlay = FALSE},
        { .value = TEN,   .color = CLUB   , .canPlay = FALSE},
        { .value = ACE,   .color = CLUB   , .canPlay = FALSE}};
    createDeck(cardDeck);
    for (int i = 0; i < 32; i++)
    {
        cardDeck[i].canPlay = FALSE;
    }
    TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(expectedCardDeck, cardDeck, sizeof(Card), 32, "Full deck wasn't generated properly");
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