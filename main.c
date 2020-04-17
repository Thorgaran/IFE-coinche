#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "play.h"

int main (int argc, char* argv[]) {
    cardType test0, test1, test2, test3, main0, main1, main2, main3, main4, main5, main6, main7;
    
    test0.value = ACE;
    test0.color = CLOVER;
    
    test1.value = QUEEN;
    test1.color = CLOVER;
    
    test2.value = NINE;
    test2.color = CLOVER;
    
    test3.value = SEVEN;
    test3.color = CLOVER;
    
    cardType testArray[] = {test0, test1, test2, test3};
    colorType testTrump = SPADE;

    main0.value = EIGHT;
    main0.color = CLOVER;

    main1.value = SEVEN;
    main1.color = CLOVER;

    main2.value = ACE;
    main2.color = HEART;

    main3.value = TEN;
    main3.color = HEART;

    main4.value = KING;
    main4.color = HEART;

    main5.value = JACK;
    main5.color = HEART;

    main6.value = JACK;
    main6.color = SPADE;

    main7.value = ACE;
    main7.color = DIAMOND;

    cardType testHand[] ={main0, main1, main2, main3, main4, main5, main6, main7};
    int testHandLength = 8;

    printf("Player %d wins the trick and gets %d points!\n", getStrongestCard(testArray, 4, testTrump, testArray[0].color), getCardArrayPoints(testArray, 4, testTrump));
    for (int i = 0; i < 8; i++) {
        findValidCardsInHand(testHand, testHandLength, testArray, 3, testTrump);
        for (int i = 0; i < testHandLength; i++) {
            printf("%d ", testHand[i].canPlay);
        }
        printf("\n");
        for (int i = 0; i < (9 - testHandLength); i++) {
            printf("  ");
        }
      
        removeCard(testHand, testHandLength, testHand[0]);
        testHandLength--;    
    }
    
    getchar();
    return EXIT_SUCCESS;
}