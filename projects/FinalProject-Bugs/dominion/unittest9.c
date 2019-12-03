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

    printf("\n*****Beginning Tribute Revealed Cards Testing*****\n");

    //Test 1: Duplicate Treasure Cards Revealed
    printf("\nBeginning Test 1: Revealed Cards are Duplicate Treasure:\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);
    int player0Hand1[8] = {tribute, estate, estate, estate, estate, estate, estate, estate};
    int player1Deck1[8] = {gold, gold, gold, gold, gold, gold, gold, gold};
    for (int i = 0; i < 8; i++) {
        G.hand[0][i] = player0Hand1[i];
        G.deck[1][i] = player1Deck1[i];
    }
    G.handCount[0] = (int)( sizeof(player0Hand1) / sizeof(player0Hand1[0]) );
    G.deckCount[1] = (int)( sizeof(player1Deck1) / sizeof(player1Deck1[0]) );
    P = G;

    choice1 = 0;
    choice2 = 0; 
    choice3 = 0;
    handPos = 0;
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);

    cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("numActions unmodified", G.numActions == P.numActions);

    //Test 2: Duplicate Victory Cards Revealed
    printf("\nBeginning Test 2: Revealed Cards are Duplicate Victory:\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);
    int player0Hand2[8] = {tribute, estate, estate, estate, estate, estate, estate, estate};
    int player1Deck2[8] = {duchy, duchy, duchy, duchy, duchy, duchy, duchy, duchy};
    for (int i = 0; i < 8; i++) {
        G.hand[0][i] = player0Hand2[i];
        G.deck[1][i] = player1Deck2[i];
    }
    G.handCount[0] = (int)( sizeof(player0Hand2) / sizeof(player0Hand2[0]) );
    G.deckCount[1] = (int)( sizeof(player1Deck2) / sizeof(player1Deck2[0]) );
    P = G;

    choice1 = 0;
    choice2 = 0; 
    choice3 = 0;
    handPos = 0;
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);

    cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("numActions unmodified", G.numActions == P.numActions);

    //Test 3: Only 1 Card Revealed
    printf("\nBeginning Test 3: Only 1 Card Revealed (Treasure):\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);
    int player0Hand3[8] = {tribute, estate, estate, estate, estate, estate, estate, estate};
    int player1Deck3[1] = {silver};
    for (int i = 0; i < 8; i++) {
        G.hand[0][i] = player0Hand3[i];
    }
    G.deck[1][0] = player1Deck3[0];
    G.handCount[0]      = (int)( sizeof(player0Hand2) / sizeof(player0Hand2[0]) );
    G.deckCount[1]      = (int)( sizeof(player1Deck2) / sizeof(player1Deck2[0]) );
    G.discardCount[1]   = 0;
    P = G;

    choice1 = 0;
    choice2 = 0; 
    choice3 = 0;
    handPos = 0;
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);

    cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("numActions unmodified", G.numActions == P.numActions);

    //Test 4: No cards revealed
    printf("\nBeginning Test 4: No Cards Revealed:\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, seed, &G);
    int player0Hand4[8] = {tribute, estate, estate, estate, estate, estate, estate, estate};
    for (int i = 0; i < 8; i++) {
        G.hand[0][i] = player0Hand4[i];
    }
    G.handCount[0]      = (int)( sizeof(player0Hand2) / sizeof(player0Hand2[0]) );
    G.deckCount[1]      = 0;
    G.discardCount[1]   = 0;
    P = G;

    choice1 = 0;
    choice2 = 0; 
    choice3 = 0;
    handPos = 0;
    G.whoseTurn = 0;
    //get card played:
    card = handCard(handPos, &G);

    cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);

    customAssert("numActions unmodified", G.numActions == P.numActions);


    return 0;

}



