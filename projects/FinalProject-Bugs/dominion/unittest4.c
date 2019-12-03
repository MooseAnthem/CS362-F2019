/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests to see if the isGameOver function checks the
**              supply count of all cards correctly
**************************************************************************/
#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Prints out the description formatted with asterisks around it
void printFormatted(char* desc) {
	printf("**************************************************************\n");
	printf("%s\n", desc);
	printf("**************************************************************\n");
}

// Prints PASSED if true and FAILED if false. Also prints the passed in description
void checkTrue(int x, int y, char* desc) {
	if (x == y) {
		printf("PASSED - %s\n", desc);
	}
	else {
		printf("FAILED - %s\n", desc);
	}
}

int main () {
	// Set up variables for tests
    int numPlayers = 2;
    int currentPlayer = 0;
    
    int k[10] = {adventurer, council_room, feast, gardens, sea_hag,
        remodel, smithy, village, baron, great_hall};

    struct gameState state;

    // Initialize the game struct
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);

    // Set the supply counts of 3 cards to 0
    state.supplyCount[adventurer] = 0;
    state.supplyCount[council_room] = 0;
    state.supplyCount[baron] = 0;

    // Print out test title
    printFormatted("UNITTEST4 - isGameOver iterates over all cards");

    // Call the function being tested
    // Signature: int isGameOver(struct gameState *state)
    // Do tests
    checkTrue(isGameOver(&state), 1, "isGameOver Returns 1");

    return 0;
}