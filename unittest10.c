#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "customAssert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int choice1, choice2, choice3, handPos, bonusVar, *bonus, card, result;
    bonus = &bonusVar; //Suppress -Wall warning about unintialized variable
    int seed = 1234;
	 
	int k[10] = { feast, ambassador, sea_hag, remodel, mine, minion, village, baron, smithy, tribute };
	
	// game states
	struct gameState G;

    printf("\n*****Beginning Ambassador Copy Counting Testing*****\n");

    //Test 1: Player has 2 copies, indicates 2 copies
    printf("\nBeginning Test 1: 2 copies in hand, 2 copies indicated:\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);

    int playerHand1[11] = {ambassador, tribute, copper, silver, gold, tribute, copper, tribute, copper, silver, gold};
    G.handCount[0] = (int) ( sizeof(playerHand1) / sizeof(playerHand1[0]));
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand1[i];
    }

    choice1 = 1;    //position of selected card
    choice2 = 2;    //indication of copies to return
    choice3 = 0;    //no effect
    handPos = 0;    //position of played ambassador
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);

    result = cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("Ambassador code proceeded successfully", result == 0);


    //Test 2: Player has 1 copy, indicates 1 copy
    printf("\nBeginning Test 2: 1 copy in hand, 1 copy indicated:\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);

    int playerHand2[9] = {ambassador, tribute, copper, silver, gold, tribute, copper, silver, gold};
    G.handCount[0] = (int) ( sizeof(playerHand2) / sizeof(playerHand2[0]));
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand2[i];
    }

    choice1 = 1;    //position of selected card
    choice2 = 1;    //indication of copies to return
    choice3 = 0;    //no effect
    handPos = 0;    //position of played ambassador
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);

    result = cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("Ambassador code proceeded successfully", result == 0);
    

    //Test 3: Player has no copies, indicates 1 copy, collision occurs
    printf("\nBeginning Test 3: No copies in hand, 1 copy indicated:\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);

    int playerHand3[11] = {ambassador, adventurer, copper, silver, gold, copper, silver, gold, copper, silver, gold};
    G.handCount[0] = (int) ( sizeof(playerHand3) / sizeof(playerHand3[0]));
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand3[i];
    }

    choice1 = 1;    //position of selected card
    choice2 = 1;    //indication of copies to return
    choice3 = 0;    //no effect
    handPos = 0;    //position of played ambassador
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);

    result = cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("Ambassador code errored out successfully", result == -1);
    

    return 0;

}