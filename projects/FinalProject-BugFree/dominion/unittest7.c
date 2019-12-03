#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "Tribute loop"

int cardEffect(int tribute, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus);

int main()
{
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus = 0;
	int seed = 1000;


	// set your card array
	int k[10] = { ambassador, council_room, feast, gardens, mine, minion, smithy, tribute, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState testG;
	

	printf("Begin Testing Tribute loop:\n");
	
	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game
	int deck[10] = {copper, adventurer, duchy, gardens, minion, ambassador, mine, smithy, baron, feast};
	G.deckCount[1] = 10;
	for (int i = 0; i < G.deckCount[1]; i++ ) {
		G.deck[1][i] = deck[i];
	}

	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = whoseTurn(&testG);
	int a = testG.numActions;
	int c = testG.coins;
	int h = testG.handCount[currentPlayer];

	//--------------------TEST: Check if for loop is working---------
	//memcpy(&testG, &G, sizeof(struct gameState));
	
	// call the Tribute function
	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
        
	printf("***************%d*********************", ((testG.numActions - a) + (testG.coins - c) + (testG.handCount[currentPlayer] - h)));
	if (((testG.numActions - a) + (testG.coins - c) + (testG.handCount[currentPlayer] - h)) == 4)
		printf("Your Tribute loop is working correctly and your function is bug free\n");
	else
		printf("Your Tribute loop has FAILED and your function has a bug \n"); 			



	printf("Test completed!\n\n");
	return 0;
}
