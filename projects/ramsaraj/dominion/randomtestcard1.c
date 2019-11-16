#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"

int main(int argc, char* argv[]) {

    int iterations = atoi(argv[1]);
    int numPlayers;
    struct gameState G, P;
    

    int kingdomCards[10] = {adventurer, tribute, ambassador, baron, minion, sea_hag, mine, cutpurse, council_room, salvager};  //Kingdom cards to use for the test.

    for (int i = 0; i < iterations; i++) {
        memset(&G, 0, sizeof(struct gameState));    //clear game state
        numPlayers = (rand() % 3) + 2;
        initializeGame(numPlayers, kingdomCards, ((rand() % 1000) + 1), &G);

        for (int player = 0; player < numPlayers; player++) {
            G.handCount[player] = (rand() % 20);
            for (int card = 0; card < G.handCount[player]; card++) {
                G.hand[player][card] = (rand() % (treasure_map + 1));
            }
            G.deckCount[player] = (rand() % 20);
            for (int card = 0; card < G.deckCount[player]; card++) {
                G.deck[player][card] = (rand() % (treasure_map + 1));
            }
            G.discardCount[player] = (rand() % 20);
            for (int card = 0; card < G.discardCount[player]; card++) {
                G.discard[player][card] = (rand() % (treasure_map + 1));
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

        printf("NUMPLAYERS:%d", G.numPlayers);
        printf("CURRENT PLAYER:%d\n", G.whoseTurn);
        P = G;  //save game state
        playTribute(G.whoseTurn, nextPlayer, &G);

        

    }
    

    return 0;

}