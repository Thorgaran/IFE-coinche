#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "play.h"

int main (int argc, char* argv[]) {
    cardType test0, test1, test2, test3;
    
    test0.value = SEVEN;
    test0.color = SPADE;
    
    test1.value = NINE;
    test1.color = SPADE;
    
    test2.value = QUEEN;
    test2.color = SPADE;
    
    test3.value = ACE;
    test3.color = DIAMOND;
    
    cardType testArray[] = {test0, test1, test2, test3};
    colorType testTrump = ALLTRUMP;

    printf("Player %d wins the trick and gets %d points!", getStrongestCard(testArray, 4, testTrump, testArray[0].color), getCardArrayPoints(testArray, 4, testTrump));

    getchar();
    return EXIT_SUCCESS;
}