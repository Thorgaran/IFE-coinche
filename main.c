#include <stdio.h>
#include <stdlib.h>
#include "coinche.h"

int main (int argc, char* argv[]) {
    cardType test0, test1, test2, test3;
    
    test0.value = NINE;
    test0.color = DIAMOND;
    
    test1.value = SEVEN;
    test1.color = SPADE;
    
    test2.value = QUEEN;
    test2.color = SPADE;
    
    test3.value = ACE;
    test3.color = DIAMOND;
    
    cardType testArray[] = {test0, test1, test2, test3};

    printf("%d", getTrickWinner(testArray, 4, NOTRUMP, testArray[0].color));
}