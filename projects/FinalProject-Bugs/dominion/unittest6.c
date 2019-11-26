#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "Feast updateCoins"

int cardEffect(int feast, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus);

int main()
{
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus = 0;
	int seed = 1000;
	int player = 0;

	// set your card array
	int k[10] = { ambassador, council_room, feast, gardens, mine, minion, smithy, village, baron, great_hall };
	//int k[1] = { feast };
	
	// declare the game state
	struct gameState G;
	struct gameState testG;
	//int currentPlayer = whoseTurn(&testG);

	printf("Begin Testing Feast case:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game

	G.handCount[player] = 1;
	G.hand[player][0] = 9;	

	//--------------------TEST--------------------------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	//choice1 = 7;  	
for (int i = 0; i < testG.handCount[player]; i++)
printf("Your hand is %d\n", testG.hand[player][i]);
printf("choice1 cost: %d\n", getCost(choice1));

	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
	
printf("Your first card cost is %d\n", getCost(testG.hand[player][0]));
printf("Your second card cost is %d\n", getCost(testG.hand[player][1]));	

	if (getCost(testG.hand[player][1]) > 5)
		printf("You can buy cards worth more than 5 and you have found a mysterious bug in this function\n");
	else
		printf("You CANNOT buy a card worth more than 5 and there is no actual bug in this function\n");

	for (int i = 0; i < testG.handCount[player]; i++)
		printf("Your hand is %d\n", testG.hand[player][i]);


	printf("Test completed!\n\n");
	return 0;
}

