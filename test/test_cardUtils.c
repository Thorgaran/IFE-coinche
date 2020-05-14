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