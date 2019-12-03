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
	int choice1 = 0;
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


	printf("Begin Testing Feast case:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game

	G.handCount[player] = 1;
	G.hand[player][0] = 9;	

	//--------------------TEST 1: Cost of 5--------------------------
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.coins = 1;
	choice1 = 2;

	printf("Testing a cost of 5:\n");
	printf("You have %d coins to buy with\n", testG.coins);

	// call the refactored function
	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	if (getCost(testG.discard[player][0]) <= 5)
		printf("You can buy cards worth 5 or less even with no money. There is no bug here\n");
	else
		printf("You CANNOT buy a card worth 5 and you found a mysterious bug in this function\n");
	
	printf("You now have %d coins\n", testG.coins);
	
	if (testG.coins == 1)
                printf("Your coins correctly reset and there is no bug\n\n");
        else
                printf("Your coins did NOT reset and there is a bug\n\n");

 
	//--------------------TEST 2: Cost of 6----------------------------------------------------------------------
        memcpy(&testG, &G, sizeof(struct gameState));
        testG.coins = 10;
	choice1 = 6;

	printf("Testing a cost of 6:\n");
        printf("You have %d coins to use\n", testG.coins);
        
	//call the refactored function
	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
        
	if (getCost(testG.discard[player][0]) > 5)
                printf("You can buy cards worth more than 5 and you found a mysterious bug in this function\n");
        else
		printf("You CANNOT buy a card worth more than 5 and ths function is now bug free\n");
	
	printf("You still have %d coins to use\n", testG.coins);

	if (testG.coins == 10)
        	printf("Your coins correctly reset and there is no bug\n\n");
	else
        	printf("Your coins did NOT reset and there is a bug\n\n");
	
	//--------------------TEST 3: Supply of 0----------------------------------------------------------------------
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	testG.supplyCount[duchy] = 0;
	testG.discardCount[player] = 0;	
	
	printf("Testing a supply of %d:\n", supplyCount(choice1, &testG));
	//call the refactored function
	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	if (testG.discardCount[player] > 0)
		printf("You can buy a card when there is one to buy, and this function is now bug free\n");
	else
		printf("You CANNOT buy a card when there aren't any, but this function is now bug free\n");
	

	printf("Test completed!\n\n");
	return 0;
}

