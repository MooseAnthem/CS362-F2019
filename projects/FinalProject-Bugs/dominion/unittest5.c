#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "scoreFor"

int scoreFor(int player, struct gameState* state);

int main()
{
	int seed = 1000;
	int player = 0;	
	
	// set your card array
	//int k[10] = { curse, curse, estate, estate, duchy, duchy, province, province, great_hall, great_hall };
	int k[1] = { curse };
	
	// declare the game state
	struct gameState G;
	struct gameState testG;
	
	int s = 0;

	printf("Begin Testing scoreFor:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game
	
	G.handCount[player] = 5;
	G.hand[player][0] = curse;
	G.hand[player][1] = curse;
	G.hand[player][2] = curse;
	G.hand[player][3] = curse;
	G.hand[player][4] = curse;

	G.discardCount[player] = 0;

	G.deckCount[player] = 5;
	G.deck[player][0] = province;
	G.deck[player][1] = province;
	G.deck[player][2] = province;
	G.deck[player][3] = province;
	G.deck[player][4] = province;

	//--------------------TEST: Check whether deck cards are being counted--------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function

	s = scoreFor(player, &testG);
	if (s != 25)
		printf("Your deck count is INcorrect because you have a bug\n");
	else
		printf("Your deck count is now correct and you no longer have a bug\n");



	printf("Test completed!\n\n");
	return 0;
}
