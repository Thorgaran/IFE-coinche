#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "play.h"

int main (int argc, char* argv[]) {
    cardType test0, test1, test2, test3, main0, main1, main2, main3, main4, main5, main6, main7;
    
    test0.value = KING;
    test0.color = CLOVER;
    
    test1.value = NINE;
    test1.color = CLOVER;
    
    test2.value = JACK;
    test2.color = SPADE;
    
    test3.value = ACE;
    test3.color = HEART;
    
    cardType testArray[] = {test0, test1, test2, test3};
    colorType testTrump = ALLTRUMP;

    main0.value = SEVEN;
    main0.color = SPADE;

    main1.value = EIGHT;
    main1.color = HEART;

    main2.value = NINE;
    main2.color = SPADE;

    main3.value = ACE;
    main3.color = HEART;

    main4.value = QUEEN;
    main4.color = HEART;

    main5.value = KING;
    main5.color = SPADE;

    main6.value = TEN;
    main6.color = SPADE;

    main7.value = ACE;
    main7.color = SPADE;

    cardType testHand[] ={main0, main1, main2, main3, main4, main5, main6, main7};

    printf("Player %d wins the trick and gets %d points!\n", getStrongestCard(testArray, 4, testTrump, testArray[0].color), getCardArrayPoints(testArray, 4, testTrump));
    findValidCardsInHand(testHand, 8, testArray, 3, testTrump);
    for (int i = 0; i < 8; i++) {
            printf("%d ", testHand[i].canPlay);
    }

    getchar();
    return EXIT_SUCCESS;
}