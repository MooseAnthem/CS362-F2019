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
	//int currentPlayer = whoseTurn(&testG);

	//G.handCount[player] = 1;
        //G.hand[player][0] = 9;	

	printf("Begin Testing Feast case:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game

	G.handCount[player] = 1;
	G.hand[player][0] = 9;	
	//G.coins = 10;

	//--------------------TEST 1: Cost of 5--------------------------
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.coins = 1;
	printf("You have %d coins to buy with\n", testG.coins);
	printf("Testing a value of 5:\n");
	// call the refactored function
	choice1 = 2;  	
	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	if (getCost(testG.discard[player][0]) <= 5)
		printf("You can buy cards worth 5 or less even with no money.  There is no bug here\n");
	else
		printf("You CANNOT buy a card worth 5 and you found a mysterious bug in this function\n");
	printf("Your coin count is now %d\n",testG.coins);
	if (testG.coins == 0)
		printf("Your coins correctly reset\n");
	else	 
		printf("Your coins did NOT reset and there is a bug\n");
/*        
	//--------------------TEST 2: Cost of 6--------------------------
        memcpy(&testG, &G, sizeof(struct gameState));
        testG.coins = 10;
	printf("Testing a value of 6:\n");
        // call the refactored function
        choice1 = 6;
        printf("You have %d coins to use\n", testG.coins);
        cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
       //printf("You have %d coins to use\n", testG.coins); 
        if (getCost(testG.discard[player][0]) > 5)
                printf("You can buy cards worth more than 5 and you found a mysterious bug in this function\n");
        else
		printf("You CANNOT buy a card worth more than 5 and ths function is now bug free\n");
	printf("You still have %d coins to use\n", testG.coins);
*/
	printf("Test completed!\n\n");
	return 0;
}

