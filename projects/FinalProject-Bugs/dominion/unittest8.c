#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "Bonus coins"

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus); 	

int main()
{
	//int card = baron;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus = 0;
	int seed = 1000;

	// set your card array
	int k[10] = { ambassador, council_room, feast, embargo, mine, minion, smithy, tribute, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState testG;
	int c = G.coins;
	//int b = G.bonus;

	printf("Begin Testing Bonus coins:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game

	//--------------------TEST 1: BARON--------------------------------
	printf("Begin Testing Baron:\n");
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (bonus == 0)
		printf("You did NOT receive bonus coins\n");
	else
		printf("You received bonus coins\n");
	
	if (c < testG.coins)
		printf("You received coins instead and your function has a bug\n\n");
	else
		printf("You correctly received no coins and your function is bug free\n\n");

	//--------------------TEST 2: MINION--------------------------------
	printf("Begin Testing Minion\n");		
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function again
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (bonus == 0)                              
 		printf("You did NOT receive bonus coins\n");
	else                                              
 		printf("You received bonus coins\n");
 
	if (c < testG.coins)                             
 		printf("You received coins instead and your function has a bug\n\n");    
	else                                              
 		printf("You correctly received no coins and your function is bug free\n\n");

 	//--------------------TEST 3: Tribute-----------------------------------
	printf("Begin Testing Tribute\n");		
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// call the refactored function again
	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
 
	if (bonus == 0)                              
		printf("You did NOT receive bonus coins\n");
	else                                              
		printf("You received bonus coins\n");
                                                   
	if (c < testG.coins)                             
		printf("You received coins instead and your function has a bug\n\n");    
	else                                              
		printf("You correctly received no coins and your function is bug free\n\n");


 	//--------------------TEST 4: Embargo-----------------------------------
	printf("Begin Testing Embargo\n");		
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// call the refactored function again
	cardEffect(embargo, choice1, choice2, choice3, &testG, handpos, &bonus);
 
	if (bonus == 0)                              
		printf("You did NOT receive bonus coins\n");
	else                                              
		printf("You received bonus coins\n");
                                                   
	if (c < testG.coins)                             
		printf("You received coins instead and your function has a bug\n\n");    
	else                                              
		printf("You correctly received no coins and your function is bug free\n\n");


	printf("Test completed!\n\n");
	return 0;
}
