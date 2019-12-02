/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests that the cost check performed in the mine case
**              statement is correct
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
    int choice1 = 1;
    int choice2 = gold;
    int handPos = 4;
    int numPlayers = 2;
    int currentPlayer = 0;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};

    struct gameState state;

    // Initialize the game struct
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = silver; // Set all of the cards to silver
    }
    state.hand[currentPlayer][0] = mine; // Set the card at position 0 to mine

    // Print out test title
    printFormatted("UNITTEST2 - Cost Check in mine");

    // Call the function being tested
    // Signature: cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
    // Do tests
    checkTrue(cardEffect(mine, choice1, choice2, 0, state, handPos, 0), 0, "cardEffect Returns 0");

    return 0;
}