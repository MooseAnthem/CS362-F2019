#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "customAssert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int choice1, choice2, choice3, handPos, bonusVar, *bonus, card;
    bonus = &bonusVar; //Suppress -Wall warning about unintialized variable
    int seed = 1234;
	 
	int k[10] = { feast, ambassador, sea_hag, remodel, mine, minion, village, baron, smithy, tribute };
	
	// game states
	struct gameState G;
    struct gameState P;

    printf("\n*****Beginning Minion Input Testing*****\n");

    printf("\nBeginning Test: `choice1` and `choice2` both set to 0:\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);

    int playerHand1[10] = {copper, copper, copper, copper, copper, copper, copper, copper, copper, minion};
    G.handCount[0] = (int) ( sizeof(playerHand1) / sizeof(playerHand1[0]));
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand1[i];
    }

    choice1 = 0;    //selector for "coin bonus"
    choice2 = 0;    //selector for "discard-and-redraw"
    choice3 = 0;    //no effect
    handPos = 9;    //position of played Minion card
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);
    P = G;

    cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("Coins unchanged", P.coins == G.coins);
    customAssert("Player's hand redrawn to 4", G.handCount[0] == 4);
    customAssert("Player's hand modified", !memcmp(&G.hand[0], &P.hand[0], sizeof(int) * MAX_HAND));



    return 0;

}