#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#include "customAssert.h"

#define FALSE 0
#define TRUE 1

int main(int argc, char* argv[]) {

    srand(time(0));

    int iterations = atoi(argv[1]);
    int numPlayers;
    struct gameState G, P;
    int totalFailedTests = 0;
    

    int kingdomCards[10] = {adventurer, tribute, ambassador, baron, minion, sea_hag, mine, cutpurse, council_room, salvager};  //Kingdom cards to use for the test.
    int validCards[16] = {adventurer, tribute, ambassador, baron, minion, sea_hag, mine, cutpurse, council_room, salvager, estate, duchy, province, copper, silver, gold}; //Used to randomly distribute cards to players

    printf("********************************************************************************\n********************************************************************************\n\t\t\t\t\tBEGINNING RANDOM TEST OF TRIBUTE\n********************************************************************************\n********************************************************************************\n");

    for (int i = 0; i < iterations; i++) {
        memset(&G, 0, sizeof(struct gameState));    //clear game state
        numPlayers = (rand() % 3) + 2;
        initializeGame(numPlayers, kingdomCards, ((rand() % 1000) + 1), &G);

        for (int player = 0; player < numPlayers; player++) {
            G.handCount[player] = (rand() % 20);
            for (int card = 0; card < G.handCount[player]; card++) {
                G.hand[player][card] = validCards[(rand() % 16)];
            }
            G.deckCount[player] = (rand() % 20);
            for (int card = 0; card < G.deckCount[player]; card++) {
                G.deck[player][card] = validCards[(rand() % 16)];
            }
            G.discardCount[player] = (rand() % 20);
            for (int card = 0; card < G.discardCount[player]; card++) {
                G.discard[player][card] = validCards[(rand() % 16)];
            }
        }

        //randomize supply counts:
        for (int card = adventurer; card <= treasure_map; card++)       	//loop all cards
        {
            for (int j = 0; j < 10; j++)           		//loop chosen cards
            {
                if (kingdomCards[j] == card)
                {
                    G.supplyCount[card] = (rand() % 11);
                    break;
                }
            }
        }

        //randomize current player:
        G.whoseTurn = (rand() % numPlayers);
        int nextPlayer = G.whoseTurn + 1;
        if (nextPlayer > (G.numPlayers - 1)) {
            nextPlayer = 0;
        }

        P = G;  //save game state

        printf("Iteration %d: Number of Players: %d - Current Player: %d - Next Player: %d\n", (i + 1), G.numPlayers, G.whoseTurn, nextPlayer);

        playTribute(G.whoseTurn, nextPlayer, &G);
        int failed = FALSE;

        //Check that single state values remain unaffected:
        if(customAssert("\tgameState.numPlayers corrupted", P.numPlayers == G.numPlayers))                      {failed = TRUE;}
        if(customAssert("\tgameState.outpostPlayed corrupted", P.outpostPlayed == G.outpostPlayed))             {failed = TRUE;}
        if(customAssert("\tgameState.outpostTurn corrupted", P.outpostTurn == G.outpostTurn))                   {failed = TRUE;}
        if(customAssert("\tgameState.whoseTurn corrupted", P.whoseTurn == G.whoseTurn))                         {failed = TRUE;}
        if(customAssert("\tgameState.phase corrupted", P.phase == G.phase))                                     {failed = TRUE;}
        if(customAssert("\tgameState.numBuys corrupted", P.numBuys == G.numBuys))                               {failed = TRUE;}
        if(customAssert("\tgameState.playedCardCount corrupted", P.playedCardCount == G.playedCardCount))       {failed = TRUE;}

        //Check whether uninvolved player's hand arrays have been corrupted:
        //NOTE: The next player's hand shouldn't be affected. Only their discard and
        //  deck array should be potentially modified by playTribute:
        for (int k = 0; k < G.numPlayers; k++) {
            if (k != G.whoseTurn) {
                char message[256];
                sprintf(message, "\tPlayer %d's hand array corrupted (G.hand[%d][MAX_HAND])", k, k);
                if(customAssert(message, memcmp(&(G.hand[k]), &(P.hand[k]), sizeof(int) * MAX_HAND) == 0)) {failed = TRUE;};
                sprintf(message, "\tPlayer %d's handCount corrupted (G.handCount[%d])", k, k);
                if(customAssert(message, P.handCount[k] == G.handCount[k])) {failed = TRUE;};
            }
        }
        //Check whether uninvolved player's decks have been corrupted:
        //Note: currentPlayer's deck should not be modified by Tribute, so they are considered
        //  "uninvolved". Only nextPlayer's deck is potentially affected by Tribute.
        for (int k = 0; k < G.numPlayers; k++) {
            if (k != nextPlayer) {
                char message[256];
                sprintf(message, "\tPlayer %d's deck array corrupted (G.deck[%d][MAX_HAND])", k, k);
                if(customAssert(message, memcmp(&(G.deck[k]), &(P.deck[k]), sizeof(int) * MAX_HAND) == 0)) {failed = TRUE;};
                sprintf(message, "\tPlayer %d's deckCount corrupted (G.deckCount[%d])", k, k);
                if(customAssert(message, P.deckCount[k] == G.deckCount[k])) {failed = TRUE;};
            }
        }
        //Check whether uninvolved player's discards have been corrupted:
        //Note: 
        for (int k = 0; k < G.numPlayers; k++) {
            if (k != nextPlayer && k != G.whoseTurn) {
                char message[256];
                sprintf(message, "\tPlayer %d's discard array corrupted (G.discard[%d][MAX_HAND])", k, k);
                if(customAssert(message, memcmp(&(G.discard[k]), &(P.discard[k]), sizeof(int) * MAX_HAND) == 0)) {failed = TRUE;};
                sprintf(message, "\tPlayer %d's discardCount corrupted (G.discardCount[%d])", k, k);
                if(customAssert(message, P.discardCount[k] == G.discardCount[k])) {failed = TRUE;};
            }
        }
        if(failed == TRUE) {totalFailedTests++;}
    }
    
    printf("\n*****TOTAL RANDOM TESTS FAILED: %d/%d", totalFailedTests, iterations);
    printf("\n*****PERCENTAGE FAILED: %f", (float)totalFailedTests / (float)iterations);

    return 0;

}